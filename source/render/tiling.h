#ifndef TILING_H
#define TILING_H

class Tiling {
public:
    struct Tile {
        int x, y, w, h;
		bool redraw = false;

        Tile();
        Tile(int ax, int ay);
        Tile(int ax, int ay, int aw, int ah);
        Tile correct(int ax, int ay, int aw, int ah) const;
        Tile correct(int aw, int ah) const;
        bool empty() const;
    };

private:
    Tile *tile = nullptr;
    int size;

    int w, h;

	int tileSize = 0x10;
    int currentTile = 0;

    void buildTiling();
    bool addTile(const Tile &rect, int &i);

public:
    void rewind();
    const Tile &current();
    void next();
    bool end();
    void resize(int aw, int ah);
};

#endif // TILING_H
