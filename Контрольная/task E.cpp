class Piece
{
public:
  virtual bool available(Cell c)
  {
    return false;
  }
  bool comp(Cell a, Cell b)
  {
    return ((a.h == b.h) && (a.v == b.v));
  }
};
class King : public Piece
{
public:
  Cell c;
  King(Cell const& cl) : c(cl){}
  King(Cell && cl) : c(cl) {}
  King() : King(Cell('A', 1)){}
  bool available(Cell s)
  {
    if(comp(s, c)) return false;
    bool buf = false;
    for (int i = -1; i < 2; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h));
    for (int i = -1; i < 2; i++)
      buf = buf || comp(s, Cell(c.v, c.h + i));
    for (int i = -1; i < 2; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h + i));
    for (int i = -1; i < 2; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h - i));
    return buf;
  }
};

class Queen : public Piece
{
public:
  Cell c;
  Queen(Cell const& cl) : c(cl){}
  Queen(Cell && cl) : c(cl) {}
  Queen() : Queen(Cell('A', 1)){}
  bool available(Cell s)
  {
    if(comp(s, c)) return false;
    bool buf = false;
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h));
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v, c.h + i));
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h + i));
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h - i));
    return buf;
  }
};

class Rook : public Piece
{
public:
  Cell c;
  Rook(Cell const& cl) : c(cl){}
  Rook(Cell && cl) : c(cl) {}
  Rook() : Rook(Cell('A', 1)){}
  bool available(Cell s)
  {
    if(comp(s, c)) return false;
    bool buf = false;
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h));
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v, c.h + i));
    return buf;
  }
};


class Bishop : public Piece
{
public:
  Cell c;
  Bishop(Cell const& cl) : c(cl){}
  Bishop(Cell && cl) : c(cl) {}
  Bishop() : Bishop(Cell('A', 1)){}
  bool available(Cell s)
  {
    if(comp(s, c)) return false;
    bool buf = false;
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h + i));
    for (int i = -8; i < 9; i++)
      buf = buf || comp(s, Cell(c.v + i, c.h - i));
    return buf;
  }
};