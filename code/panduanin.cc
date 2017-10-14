struct P
{
  double x, y;
};
struct Segment
{
  P p, q;
};
double ccw(P a, P b, P c)
{
   return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
bool intersects(Segment a, Segment b)
{
   if (ccw(a.p, a.q, b.p) * ccw(a.p, a.q, b.q) > 0) return false;
   if (ccw(b.p, b.q, a.p) * ccw(b.p, b.q, a.q) > 0) return false;
   return true;
}