long plus(long, long);

void sumstore (long x, long y, long *dest){
    long t = plus(x,y);
    *dest = t;
}

void sumstore (long x, long y, long *dest);

int main(){
    long d;
    sumstore(2, 3, &d);
    return d;
}