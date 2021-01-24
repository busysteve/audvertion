#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

const double PI = 3.141592653589793238463;



int main( int argc, char**argv )
{


	double sampleRate = 44100.0;
	double amp = 1.0;
	std::string format = "s16ne";
	double cF = 3000.0; 
	double beta = 1.0; 
	int Argc = 0;
	
	while( ++Argc < argc )
	{
		char* Arg = argv[ Argc ];
		char** Argv = &argv[ Argc ];
		
		if( Arg[0] == '-' )
		{
			switch( Arg[1] )
			{
				case 'b':
					beta = atoi( Argv[1] );
					Argc++;
				break;
				case 'c':
					cF = atoi( Argv[1] );
					Argc++;
				break;
				case 'f':
					format = Argv[1];
					Argc++;
				break;
				case 'r':
					sampleRate = atof( Argv[1] );
					Argc++;
				break;
				case 'a':
					amp = atof( Argv[1] );
					Argc++;
				break;
				case 'x':
					std::cout
						<< "Carrier Freq:" << cF << std::endl
						<< "Beta : " << beta  << std::endl
						<< "Rate : " << sampleRate << std::endl
						<< "Amp : " << amp << std::endl
						<< "Format : " << format << std::endl
						<< std::endl;
						return 0;
				break;
				default:
					std::cout
					<< "	-u = upper frequency " << std::endl 
					<< "	-l = lower frequency " << std::endl 
					<< "	-r = sample rate " << std::endl 
					<< "	-a = amplitude 0.0 to 1.0 " << std::endl 
					<< "	-f = Format of sound: " << std::endl 
					<< "		s16 " << std::endl 
					<< "		float32 " << std::endl 
					<< std::endl;
					return 0;
					//break;
			}
		}
	
	
	} 



	int result;

	// filter a buffer of input samples, in-place
	
	if( format == "s16" || format == "s16ne" )
	{
		short data[360]; 
		double sample, samples=0, result=0;
		double beta = 0.7;
		double t=1.0;
		
		while( ( result = fread(&data,sizeof(data),1,stdin) ) == 1 ) {
			for( int i=0; i < 360; i++,t++ ) {
				sample += ( ( (double)data[i] ) / ( (double)SHRT_MAX ) );
				
				samples += beta* sample;

				result = std::sin(( ( (( (cF+sample*beta)*t)) ) * (360.0/sampleRate) * (PI/180.0)) );
				
				result *= amp;
				
				data[i] = (short)(result * SHRT_MAX) ;
			}
			fwrite( &data, sizeof(data), 1, stdout );
		}
	}

	return 0;
}

