#include"tiling.h"

static int _div(int num, int den) {
    if(den<0){num=-num;den=-den;}
    return (num<0)?(((num+1)/den)-1):(num/den);
}

Tiling::Tile::Tile() {

}
Tiling::Tile::Tile(int ax, int ay) {
    x = ax;
    y = ay;
}
Tiling::Tile::Tile(int ax, int ay, int aw, int ah) : Tile(ax,ay) {
    w = aw;
    h = ah;
}
Tiling::Tile Tiling::Tile::correct(int ax, int ay, int aw, int ah) const {
    Tile corr = *this;
    if(x + w >= aw)
    {
        corr.w -= x + w - aw;
    }
    if(y + h >= ah)
    {
        corr.h -= y + h - ah;
    }
    if(x < ax)
    {
        corr.x = ax;
        corr.w += x - ax;
    }
    if(y < ay)
    {
        corr.y = ay;
        corr.h += y - ay;
    }
    return corr;
}
Tiling::Tile Tiling::Tile::correct(int aw, int ah) const {
    return correct(0,0,aw,ah);
}
bool Tiling::Tile::empty() const {
    if(w > 0 && h > 0)
    {
        return false;
    }
    return true;
}

void Tiling::buildTiling() {
    size = 0;
    if(tile != nullptr) {
        delete[] tile;
    }

    int fx = 2*(_div(w - tileSize,2*tileSize) + 1) + 1;
    int fy = 2*(_div(h - tileSize,2*tileSize) + 1) + 1;
    int fn = fx*fy;

    size = fn;
    tile = new Tile[size];

    int i = 0;
    Tile fb;
    fb.x = w/2 - tileSize/2;
    fb.y = h/2 - tileSize/2;
    fb.w = tileSize;
    fb.h = tileSize;
    tile[i++] = fb.correct(w,h);

    for(int ig = 1; ; ig++){
        fb.x += tileSize;
        addTile(fb,i);
        for(int j = 0; j < 2*ig-1; j++){
            fb.y -= tileSize;
            addTile(fb,i);
        }
        for(int j = 0; j < 2*ig; j++){
            fb.x -= tileSize;
            addTile(fb,i);
        }
        for(int j = 0; j < 2*ig; j++){
            fb.y += tileSize;
            addTile(fb,i);
        }
        for(int j = 0; j < 2*ig; j++){
            fb.x += tileSize;
            addTile(fb,i);
        }
        if(ig > fx && ig > fy){
            break;
        }
    }
    size = i;
}

bool Tiling::addTile(const Tile &rect, int &i) {
    Tile corr = rect.correct(w,h);
    if(!corr.empty())
    {
        tile[i++] = corr;
        return true;
    }
    return false;
}

void Tiling::rewind() {
    currentTile = 0;
}

const Tiling::Tile &Tiling::current() {
    return tile[currentTile];
}

void Tiling::next() {
    currentTile++;
}

bool Tiling::end() {
    if(currentTile < size) {
        return false;
    }
    return true;
}
void Tiling::resize(int aw, int ah) {
    w = aw;
    h = ah;

    buildTiling();
    currentTile = 0;
}
