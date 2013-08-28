// Reference :
// Calvin R. Maurer, Jr., Rensheng Qi, and Vijay Raghavan
// A Linear Time Algorithm for Computing Exact Euclidean Distance Transforms of Binary Images in Arbitrary Dimensions.
// IEEE Trans. Pattern Anal. Mach. Intell. 25, 2 (February 2003), 265-270. DOI=10.1109/TPAMI.2003.1177156 

#ifndef __DT_HPP__
#define __DT_HPP__ 1
#include <vector>
#include <cmath>
bool compute_distance_field ( std::vector< std::vector< std::vector< char  > > >&  binary,
                              std::vector< std::vector< std::vector< float > > >&  df )
{
        const static int MAX_DIST = 10000000;
        // sx, sy, sz : size of volume.
        const int sz = binary.size();
        const int sy = binary[0].size();
        const int sx = binary[0][0].size();
	
        df.clear();
        df.assign ( sz, std::vector<std::vector<float> >( sy, std::vector<float>( sx, 0 ) ) );

        for( int z = 0 ; z < sz ; ++z ) {
                std::vector< std::vector<int> > zz( sy , std::vector<int>( sx, MAX_DIST ) );
                for( int y = 0 ; y < sy ; ++y ) {
                        for( int x = 0 ; x < sx ; ++x ) {
                                for( int dz = 0 ; dz < sz ; ++dz ) {
                                        if ( binary[dz][y][x] != 1 ) continue;
                                        const int dd =  ( dz - z ) * ( dz - z );
                                        if( dd < zz[y][x] ) zz[y][x] = dd;
                                }
			}
                }
                for( int y = 0 ; y <  sy ; ++y ) {
                        std::vector<int> yyzz ( sx, MAX_DIST ) ;
                        for( int x = 0 ; x < sx ; ++x ) {
                                for( int dy = 0 ; dy < sy ; ++dy ) {
                                        if ( zz[dy][x] == MAX_DIST ) continue;
                                        const int yy =  ( dy - y ) * ( dy - y );
                                        const int dd =  zz[dy][x] + yy;
                                        if( dd < yyzz[x] ) yyzz[x] = dd;
                                }
                        }
                        for( int x = 0 ; x < sx ; ++x ) {
                                int xxyyzz = MAX_DIST;
                                for( int dx = 0 ; dx < sx ; ++dx ) {
                                        if ( yyzz[dx] == MAX_DIST ) continue;
                                        const int xx = ( dx - x ) * ( dx - x );
                                        const int dd = yyzz[dx] + xx;
                                        if( dd < xxyyzz ) xxyyzz = dd;
                                }
                                df[z][y][x] = std::sqrt( static_cast<float>( xxyyzz ) );
                        }
                }
        }
        return true;
}
#endif//__DT_HPP__
