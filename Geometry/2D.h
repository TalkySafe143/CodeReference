/*
2D geometry utilities
---
Source: https://github.com/ahoraSoyPeor/notebook_descomUNAL
*/

typedef long double lf;
const lf EPS = 1e-8L;
const lf E0 = 0.0L;//Keep = 0 for integer coordinates, otherwise = EPS
const lf INF = 5e9;

enum {OUT,IN,ON};

struct pt {
  lf x,y;
  pt(){}
  pt(lf a , lf b): x(a), y(b){}

  pt operator - (const pt &q ) const {
    return {x - q.x , y - q.y };
  }

  pt operator + (const pt &q ) const {
    return {x + q.x , y + q.y };
  }

  pt operator * (const lf &t ) const {
    return {x * t , y * t };
  }

  pt operator / (const lf &t ) const {
    return {x / t , y / t };
  }

  bool operator < ( const pt & q ) const {
    if( fabsl( x - q.x ) > E0 ) return x < q.x;
    return y < q.y;
  }

  void normalize() {
    lf norm = hypotl( x, y );
    if( fabsl( norm ) > EPS )
      x /= norm, y /= norm;
  }
};

pt rot90( pt p ) { return { -p.y, p.x }; }
pt rot( pt p, lf w ) {
  return { cosl( w ) * p.x - sinl( w ) * p.y, sinl( w ) * p.x + cosl( w ) * p.y };
}

lf norm2 ( pt p ) { return p.x * p.x + p.y * p.y; }
lf dis2 ( pt p, pt q ) { return norm2(p-q); }

lf norm ( pt p ) { return hypotl ( p.x, p.y ); }
lf dis( pt p, pt q ) { return norm( p - q ); }

lf dot( pt p, pt q ) { return p.x * q.x + p.y * q.y; }
lf cross( pt p, pt q ) { return p.x * q.y - q.x * p.y ; }

lf orient( pt a, pt b, pt c ) { return cross( b - a, c - a ); };

lf angle( pt a, pt b){ return atan2(cross(a, b), dot(a, b)); }

lf abs(pt a) { return sqrt(a.x * a.x + a.y * a.y); }

bool in_angle( pt a, pt b, pt c, pt p ) {
  //assert( fabsl( orient( a, b, c ) ) > E0 );
  if( orient( a, b, c ) < -E0 )
    return orient( a, b, p ) >= -E0 || orient( a, c, p ) <= E0;
  return orient( a, b, p ) >= -E0 && orient( a, c, p ) <= E0;
}

struct line {
  pt nv;
  lf c;

  line( pt _nv, lf _c ) : nv( _nv ), c( _c ) {}

  line ( pt p, pt q ) {
    nv = { p.y - q.y, q.x - p.x };
    c = -dot( p, nv );
  }

  lf eval( pt p ) { return dot( nv, p ) + c; }

  lf distance2( pt p ) {
    return eval( p ) / norm2( nv ) * eval( p );
  }

  lf distance( pt p ) {
    return fabsl( eval( p ) ) / norm( nv );
  }

  pt projection( pt p ) {
    return p - nv * ( eval( p ) / norm2( nv ) );
  }
};

pt lines_intersection( line a, line b ) {
  lf d = cross( a.nv, b.nv );
  //assert( fabsl( d ) > E0 );
  lf dx = a.nv.y * b.c - a.c * b.nv.y;
  lf dy = a.c * b.nv.x - a.nv.x * b.c;
  return { dx / d, dy / d };
}

// A line segment bisector divides the line segment into 2 equal parts
line bisector( pt a, pt b ) {
  pt nv = ( b - a ), p = ( a + b ) * 0.5L;
  lf c = -dot( nv, p );
  return line( nv, c );
}

struct Circle {
  pt center;
  lf r;

  Circle( pt p, lf rad ) : center( p ), r( rad ) {};

  Circle( pt p, pt q ) {
    center = ( p + q ) * 0.5L;
    r = dis( p, q ) * 0.5L;
  }

  Circle( pt a, pt b, pt c ) {
    line lb = bisector( a, b ), lc = bisector( a, c );
    center = lines_intersection( lb, lc );
    r = dis( a, center );
  }

  int contains( pt &p ) {
    lf det = r * r - dis2( center, p );
    if( fabsl( det ) <= E0 ) return ON;
    return ( det > E0 ? IN : OUT );
  }
};

lf part(pt a, pt b, lf r) {
  lf l = abs(a-b);
  pt p = (b-a)/l;
  lf c = dot(a, p), d = 4.0 * (c*c - dot(a, a) + r*r);
  if (d < EPS) return angle(a, b) * r * r * 0.5;
  d = sqrt(d) * 0.5;
  lf s = -c - d, t = -c + d;
  if (s < 0.0) s = 0.0; else if (s > l) s = l;
  if (t < 0.0) t = 0.0; else if (t > l) t = l;
  pt u = a + p*s, v = a + p*t;
  return (cross(u, v) + (angle(a, u) + angle(v, b)) * r * r) * 0.5;
}

lf circle_poly_intersection( Circle c, vector<pt> p){
  lf ans = 0;
  int n = p.size();
  for (int i = 0; i < n; i++) {
    ans += part(p[i]-c.center, p[(i+1)%n]-c.center, c.r);
  }
  return abs(ans);
}

vector< pt > circle_line_intersection( Circle c, line l ) {
  lf h2 = c.r * c.r - l.distance2( c.center );
  if( fabsl( h2 ) < EPS ) return { l.projection( c.center ) };
  if( h2 < 0.0L ) return {};

  pt dir = rot90( l.nv );
  pt p = l.projection( c.center );
  lf t = sqrtl( h2 / norm2( dir ) );

  return { p + dir * t, p - dir * t };
}

vector< pt > circle_circle_intersection( Circle c1, Circle c2 ) {
  pt dir = c2.center - c1.center;
  lf d2 = dis2( c1.center, c2.center );

  if( d2 <= E0 ) {
    //assert( fabsl( c1.r - c2.r ) > E0 );
    return {};
  }

  lf td = 0.5L * ( d2 + c1.r * c1.r - c2.r * c2.r );
  lf h2 = c1.r * c1.r - td / d2 * td;

  pt p = c1.center + dir * ( td / d2 );
  if( fabsl( h2 ) < EPS ) return { p };
  if( h2 < 0.0L ) return {};

  pt dir_h = rot90(dir) * sqrtl( h2 / d2 );
  return { p + dir_h, p - dir_h };
}

vector< pt > convex_hull( vector< pt > v ) {
  sort( v.begin(), v.end() );//remove repeated points if needed
  const int n = v.size();
  if( n < 3 ) return v;
  vector< pt > ch( 2 * n );

  int k = 0;
  for( int i = 0; i < n; ++ i ) {
    while( k > 1 && orient( ch[k-2], ch[k-1], v[i] ) <= E0 )
      --k;
    ch[k++] = v[i];
  }

  const int t = k;
  for( int i = n - 2; i >= 0; -- i ) {
    while( k > t && orient( ch[k-2], ch[k-1], v[i] ) <= E0 )
      --k;
    ch[k++] = v[i];
  }
  ch.resize( k - 1 );
  return ch;
}

int point_in_polygon( const vector< pt > &pol, const pt &p ) {
  int wn = 0;
  for( int i = 0, n = pol.size(); i < n; ++ i ) {
    lf c = orient( p, pol[i], pol[(i+1)%n] );
    if( fabsl( c ) <= E0 && dot( pol[i] - p, pol[(i+1)%n] - p ) <= E0 ) return ON;
    if( c > 0 && pol[i].y <= p.y + E0 && pol[(i+1)%n].y - p.y > E0 ) ++wn;
    if( c < 0 && pol[(i+1)%n].y <= p.y + E0 && pol[i].y - p.y > E0 ) --wn;
  }
  return wn ? IN : OUT;
}