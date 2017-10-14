int calc(int y,int m,int d)
{ 
    if (m < 3) m += 12, y--;
    int w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4
        - y / 100 + y / 400) % 7;    
    return w;
}
bool isRun(int YYYY)
{
    return (YYYY % 4 == 0 && YYYY % 100 != 0) || (YYYY % 400 == 0);
}