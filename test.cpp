int main(){
    
    int n = 3;
    
    int m = 4;
    
    int a = n + m;

    if (a > 5) {
        a = 5;
    } else {
        a = 6;
    }

    for (int i = 0; i < 10; i++) {
        a = a + 1;
    }

    while (a > 0) {
        a = a - 1;
    }

    return 0;
}