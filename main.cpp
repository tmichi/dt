#include "dt.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
int main ( int argc, char** argv )
{
        const int sx = 128;
        const int sy = 128;
        const int sz = 128;

        std::vector<std::vector<std::vector<char> > > binary( sz, std::vector< std::vector<char> > ( sy, std::vector<char>( sx, 0 ) ) );
        for( int i = 0 ; i < 30 ; ++i ) {
                int x = rand() % 128;
                int y = rand() % 128;
                int z = rand() % 128;
                binary[z][y][x] = 1;
        }
        std::vector<std::vector<std::vector<float> > > result;
        if( !compute_distance_field( binary, result ) ) {
		std::cerr<<"distance field computation failed."<<std::endl;
		return -1;
        }
	
        std::ofstream fout( "result-dist.raw", std::ios::binary );
        for( int z = 0 ; z < sz ; ++z ) {
                for( int y = 0 ; y < sy ; ++y ) {
                        fout.write( ( char* )( &result[z][y][0] ), sizeof( float ) * sx );
                }
        }	
        return 0;
}
