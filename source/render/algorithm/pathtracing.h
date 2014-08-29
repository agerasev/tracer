#ifndef PATHTRACING_H
#define PATHTRACING_H

#include<4u/rand/contrand.hpp>

#include<render/path.h>
#include<render/params.h>
#include<render/container/surface.h>
#include<render/scene.h>

class PathTracing
{
private:
	bool quited = false;

	Color trace(
			const Scene *scene,
			const vec2 &pix,
			const RenderParams &params,
			ContRand &rand
			) const
	{
		Path path = Path(scene->getSpectator()->cast(pix,params.primary_scene,rand));

		/* Computes interaction between ray and scene */
		std::function<Color(Path&,int,const SceneParams&)> build = [&build,scene,&params,&rand](
				Path &path,
				int depth,
				const SceneParams &spar
				)
		{
			if(depth < 0)
			{
				return Color(0,0,0);
			}

			/* Function for adding secondary rays */
			std::function<void(Ray &&)> add = [&path](Ray &&ray)
			{
				/* Diffuse rays shouldn't hit emitters */
				if(Ray::DIFFUSE & ray.flag)
				{
					ray.mask &= ~Ray::EMIT;
				}
				path.paths.push_back(Path(ray));
			};

			/* Finds intersection with scene */
			const Object *obj = scene->intersect(path.ray,path.state,spar,rand);

			if(path.object != nullptr && path.object != obj)
			{
				return Color(0,0,0);
			}

			path.object = obj;

			/* Whether intersection has been found */
			if(path.object != nullptr)
			{
				/* Traces ray */
				path.glow = path.object->trace(path.ray,path.state,add,spar,rand);

				/* If objects produces diffuse ray */
				if(path.object->getInteractionKind(path.state) & Ray::DIFFUSE)
				{
					/* Force casts ray to emitters */
					const std::list<const Emitter*> *emitters = scene->getEmitters();
					for(const Emitter *emi : *emitters)
					{
						std::function<void(const vec3 &, double)> add_attraction =
								[&path,emi,&spar,&rand](const vec3 &d, double p)
						{
							std::function<void(Ray &&)> add = [&path,emi](Ray &&ray)
							{
								ray.mask |= Ray::EMIT;
								path.paths.push_back(Path(ray,emi));
							};
							path.object->cast(path.ray,path.state,d,p,add,spar,rand);
						};
						emi->attract(path.state.point,add_attraction,spar,rand);
					}
				}
			}
			else
			{
				path.glow = scene->getAtmosphereColor(path.ray);
			}

			Color sum = Color(0,0,0);
			for(Path p : path.paths)
			{
				const SceneParams *par = &params.secondary_scene;
				if(p.ray.flag & (Ray::REFLECT | Ray::REFRACT))
				{
					par = &params.primary_scene;
				}
				sum += build(p, depth -	1, *par);
			}
			return sum + path.ray.color*path.glow;
		};

		return build(path,params.recursion_depth,params.primary_scene);
	}

public:
	void perform(
			const Scene *scene,
			Surface &surface,
			const RenderParams &params,
			ContRand &rand
			)
	{
		const int detailing = params.detailing;
		const int w = surface.w(), h = surface.h();
		for(int iy = 0; iy < h; ++iy)
		{
			for(int ix = 0; ix < w; ++ix)
			{
				Color color = Color(0,0,0);
				for(int jy = 0; jy < detailing; ++jy)
				{
					Color lcolor = Color(0,0,0);
					for(int jx = 0; jx < detailing; ++jx)
					{
						lcolor += trace(
									scene,
									surface.getCoord(
										ix + static_cast<double>(jx)/detailing - 0.5,
										iy + static_cast<double>(jy)/detailing - 0.5
										),
									params,
									rand
									);
						if(quited)
						{
							return;
						}
					}
					color += lcolor/detailing;
				}
				surface.setPixel(
							color/detailing,
							ix,iy
							);
			}
		}
	}
	void interrupt()
	{
		quited = true;
	}
};

#endif // PATHTRACING_H
