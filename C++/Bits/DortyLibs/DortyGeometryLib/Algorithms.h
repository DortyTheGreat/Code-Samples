/// Здесь собраны алгоритмы, которые прикольные))

#include <cassert>

/// Дан многоугольник, постройте такую фигуру, описывающую многоугольник, что никакая точка на ней не лежит ближе чем на L расстояния к многоугольнику. Минимизируйте длину такой фигуры. Возвращает длину фигуры.
long double lots_of_points_in_polygon_intersection(Polygon p, long double L){

    long double ret = 0;

    int sz = p.size() - 2;

    for(int i = 0;i<sz;i++){
        /// i, i+1
        ret += Segment(p.points[i],p.points[i+1]).getLength();
    }

}



long double Cake_algo(Polygon p){
    double l = 1e10;
    double r = -1e10;



    if (p.size_ < 3){
        assert(false);
    }

    int sz = p.size_;
    for(int i = 0;i<sz;i++){
        l = min(p.points[i].X,l);
        r = max(p.points[i].X,r);
    }

    double ll = l;
    double rr = r;


    const int itterations = 500;
    double m;
    bool bkwd = 1;

    double delta0;

    const int bg = itterations / 2;

    const double two = 2;

    double Areas[2];

    int happened = 0;
    int h2 = 0;

    for(int i = 0;i<itterations;i++){
        happened = 0;

        if (i == bg){
            //cout << delta0  << endl;
        }

        if ( (min(Areas[0],Areas[1]) < 1) ){
            cout << "REVERSE!" << endl;
            bkwd = !bkwd;
            h2++;
            l = ll;
            r = rr;
        }

        m = (l+r)/two ;


        Areas[0] = 0; Areas[1] = 0;
        bool flag = bkwd;



        for(int i =0;i<p.size_ - 1;i++){
            if ( m >= min(p.points[i].X,p.points[i+1].X) && m < max(p.points[i].X,p.points[i+1].X)){
                /// Произошёл переход
                happened++;
                double Y_val = Line(p.points[i],p.points[i+1]).getY_byX(m);

                Areas[flag] += (p.points[i].X - m)*(p.points[i].Y + Y_val);
                flag = !flag;
                Areas[flag] += (m - p.points[i+1].X)*(Y_val + p.points[i+1].Y);
            }else{
                Areas[flag] += (p.points[i].X - p.points[i+1].X)*(p.points[i].Y + p.points[i+1].Y);
            }
        }

        if ( m >= min(p.points[p.size_ - 1].X,p.points[0].X) && m < max(p.points[p.size_ - 1].X,p.points[0].X)){
            /// Произошёл переход
            happened++;
            double Y_val = Line(p.points[p.size_ - 1],p.points[0]).getY_byX(m);

            Areas[flag] += (p.points[p.size_ - 1].X - m)*(p.points[p.size_ - 1].Y + Y_val);
            flag = !flag;
            Areas[flag] += (m - p.points[0].X)*(Y_val + p.points[0].Y);
        }else{
            Areas[flag] += (p.points[p.size_ - 1].X - p.points[0].X)*(p.points[p.size_ - 1].Y + p.points[0].Y);
        }

        if (happened != 2){
            assert(false);
        }

        /// Не стоит бояться, это просто ещё один вызов for, но для 0 и sz-1

        Areas[0] = abs(Areas[0] / 2);
        Areas[1] = abs(Areas[1] / 2);

        cout << Areas[0] << " " << Areas[1] << endl;

        if ( (Areas[0] < Areas[1]) ){
            l = m;
        }else{
            r = m;
        }

    }

    if ( h2 >= 10 ){
        //assert(false);
    }

    return m;

}
