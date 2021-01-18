#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "Biquad.h"
#include <climits>


float process( std::vector<Biquad*> &biquads, float signal )
{
	float data = signal;
	for( auto b : biquads )
		data = b->process( data );

	return data;
}


int main( int argc, char**argv )
{


	double Q =1.0;
	double freq = 1000.0;
	double sampleRate = 44100.0;
	double gain = 0.0;
	std::string type;
	std::string format = "s16ne";
	int filterType = bq_type_lowpass;
	int layers = 1;
	
	int Argc = 0;
	
	while( ++Argc < argc )
	{
		char* Arg = argv[ Argc ];
		char** Argv = &argv[ Argc ];
		
		if( Arg[0] == '-' )
		{
			switch( Arg[1] )
			{
				case 'F':
					format = Argv[1];
					Argc++;
				break;
				case 'l':
					layers = atoi( Argv[1] );
					Argc++;
				break;
				case 'f':
					freq = atof( Argv[1] );
					Argc++;
				break;
				case 'q':
					Q = atof( Argv[1] );
					Argc++;
				break;
				case 'r':
					sampleRate = atof( Argv[1] );
					Argc++;
				break;
				case 'g':
					gain = atof( Argv[1] );
					Argc++;
				break;
				case 'x':
					std::cout
						<< "Filter Type: " << type << std::endl
						<< "Gain : " << gain  << std::endl
						<< "Freq : " << freq << std::endl
						<< "Rate : " << sampleRate << std::endl
						<< "layers : " << layers << std::endl
						<< "Format : " << format << std::endl
						<< std::endl;
						return 0;
				break;
				case 't':
					type = Argv[1];
					
					if( type == "highpass" )
						filterType = bq_type_highpass;
					else if( type == "bandpass" )
						filterType = bq_type_bandpass;
					else if( type == "notch" )
						filterType = bq_type_notch;
					else if( type == "peak" )
						filterType = bq_type_peak;
					else if( type == "lowshelf" )
						filterType = bq_type_lowshelf;
					else if( type == "highshelf" )
						filterType = bq_type_highshelf;
					else // lowpass
						filterType = bq_type_lowpass;
					
					Argc++;
				break;
				default:
					std::cout
					<< "	-f = frequency " << std::endl 
					<< "	-q = Q " << std::endl 
					<< "	-r = sample rate " << std::endl 
					<< "	-g = gain in db " << std::endl 
					<< "	-F = Format of sound: " << std::endl 
					<< "		s16 " << std::endl 
					<< "		float32 " << std::endl 
					<< "	-l = layers of biquads: " << std::endl 
					<< "	-t = one of type: " << std::endl 
					<< "		lowpass " << std::endl 
					<< "		highpass " << std::endl 
					<< "		bandpass " << std::endl 
					<< "		notch " << std::endl 
					<< "		peak " << std::endl 
					<< "		lowshelf " << std::endl 
					<< "		highshelf " << std::endl 
					<< std::endl;
					return 0;
					//break;
			}
		}
	
	
	} 





	//Biquad *lpFilter = new Biquad();	// create a Biquad, lpFilter;	
	std::vector<Biquad*> biquads;

	for( int i=0; i<layers; i++ )
		biquads.push_back( new Biquad() );

	for( auto b : biquads )
		b->setBiquad( filterType, freq / sampleRate, Q, gain );

	//lpFilter->setBiquad(filterType, freq / sampleRate, Q, gain);
	//lpFilter->setBiquad(bq_type_highpass, 400 / 44000, 0.707, 0);


	int result;

	// filter a buffer of input samples, in-place
	
	if( format == "s16" || format == "s16ne" )
	{
		short data[64]; 
		float sample;
		while( ( result = fread(&data,sizeof(data),1,stdin) ) != sizeof(data) ) {
			for( int i=0; i < 64; i++ ) {
				sample = ( (float)data[i] ); // / (float)SHRT_MAX;
				data[i] = ((short)process( biquads, sample ) ); // * SHRT_MAX;
			}
			fwrite( &data, sizeof(data), 1, stdout );
		}
	}
	else if( format == "float32" || format == "float" || format == "" )
	{
		float data[64]; 
		while( ( result = fread(&data,sizeof(data),1,stdin) ) != sizeof(data) ) {
			for( int i=0; i < 64; i++ )
			{
				data[i] = process( biquads, data[i] );
			}
			fwrite( &data, sizeof(data), 1, stdout );
		}
	}

	return 0;
}

