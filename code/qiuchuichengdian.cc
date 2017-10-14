using namespace std;
const double eps = 1e-10;
double add (double a, double b)
{
  if (abs(a + b) < eps * (abs(a) + abs(b))) return 0;
  return a + b;
}
struct P
{
  double x, y;
  P(){}
  P(double x, double y):x(x),y(y){}
  P operator + (P p)
  {
    return P(add(x, p.x), add(y, p.y));
  }
  P operator - (P p)
  {
    return P(add(x, -p.x), add(y, -p.y));
  }
  P operator * (double d)
  {
    return P(x * d, y * d);
  }
};
double det(P p1, P p2)
{
  return add(p1.x * p2.y, -p1.y * p2.x);
}
bool g_equal(double a, double b)
{
  if (a > b - eps && a < b + eps) return true;
  return false;
}
//求p关于p1, p2所成直线的对称点
P symmetric_point(P p, P p1, P p2)
{
  //直线与x轴垂直
	if (g_equal(p1.x, p2.x)) return P(2 * p1.x - p.x, p.y);
  double k = (p1.y - p2.y ) / (p1.x - p2.x);
  if (g_equal(k, 0)) return P(p.x, 2 * p1.y - p.y);
  double x = (2*k*k*p1.x + 2*k*p.y - 2*k*p1.y - k*k*p.x + p.x) / (1 + k * k);
  double y = p.y - (x - p.x) / k;
  return P(x, y);
}
P intersection(P p1, P p2, P q1, P q2)
{
  return p1 + (p2 - p1) * (det(q2 - q1, q1 - p1) / det(q2 - q1, p2 - p1));
}