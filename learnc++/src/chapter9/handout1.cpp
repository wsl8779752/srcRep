    sort(v.begin(),v.end());  
    for( i = v.begin(); i < v.end() - 1;i ++ )
        for(j = v.begin()+1; j<v.end();j++) {
            if(binary_search(v.begin(),v.end(),Point( j->x, i->y)) &&
                binary_search(v.begin(),v.end(),Point(i->x,j->y))  &&
                Point(j->x,i->y)<Point(i->x, j->y)    &&
                 *i < Point(j->x,i->y) )
                nTotalNum ++;
        }
    cout << nTotalNum;

