#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<tuple<long long, long long, long long>> answer = {
    make_tuple(0LL,0LL,0LL),
    make_tuple(0LL,0LL,1LL),
    make_tuple(0LL,1LL,1LL),
    make_tuple(1LL,1LL,1LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(-1LL,-1LL,2LL),
    make_tuple(0LL,-1LL,2LL),
    make_tuple(0LL,0LL,2LL),
    make_tuple(0LL,1LL,2LL),
    make_tuple(1LL,1LL,2LL),
    make_tuple(-2LL,-2LL,3LL),
    make_tuple(7LL,10LL,-11LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(-1LL,2LL,2LL),
    make_tuple(-511LL,-1609LL,1626LL),
    make_tuple(1LL,2LL,2LL),
    make_tuple(-1LL,-2LL,3LL),
    make_tuple(0LL,-2LL,3LL),
    make_tuple(1LL,-2LL,3LL),
    make_tuple(-11LL,-14LL,16LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(-2901096694LL,-15550555555LL,15584139827LL),
    make_tuple(-1LL,-1LL,3LL),
    make_tuple(0LL,-1LL,3LL),
    make_tuple(0LL,0LL,3LL),
    make_tuple(0LL,1LL,3LL),
    make_tuple(1LL,1LL,3LL),
    make_tuple(-283059965LL,-2218888517LL,2220422932LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(8866128975287528LL,-8778405442862239LL,-2736111468807040LL),
    make_tuple(-1LL,2LL,3LL),
    make_tuple(0LL,2LL,3LL),
    make_tuple(1LL,2LL,3LL),
    make_tuple(0LL,-3LL,4LL),
    make_tuple(1LL,-3LL,4LL),
    make_tuple(117367LL,134476LL,-159380LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(0LL,0LL,0LL),
    make_tuple(-80538738812075974LL,80435758145817515LL,12602123297335631LL),
    make_tuple(2LL,2LL,3LL),
    make_tuple(-5LL,-7LL,8LL),
    make_tuple(2LL,-3LL,4LL),
    make_tuple(-2LL,3LL,3LL),
    make_tuple(6LL,7LL,-8LL),
    make_tuple(-23LL,-26LL,31LL),
    make_tuple(0LL,0LL,0LL)
  };
  
  int N;
  scanf("%d", &N);

  if (N == 2) {
    puts("3737830626090 1490220318001 -3815176160999");
    return 0;
  }

  if (N % 9 == 4 || N % 9 == 5) {
    puts("0");
  } else {
    long long X = get<0>(answer[N]);
    long long Y = get<1>(answer[N]);
    long long Z = get<2>(answer[N]);
    printf("%lld %lld %lld\n", X, Y, Z);
  }
}
