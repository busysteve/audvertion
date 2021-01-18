#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <climits>


int main( int argc, char**argv )
{


	std::string type;
	std::string format = "s16ne";
	
	int Argc = 0;

	std::vector<std::string> filepaths;

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
				case 'f':
					filepaths.push_back( Argv[1] );
					Argc++;
				break;
				default:
					std::cout
					<< "	-f = file name (more than one should be supplied) " << std::endl 
					<< "	-F = Format of sound: " << std::endl 
					<< "		s16 " << std::endl 
					<< "		float32 " << std::endl 
					<< std::endl;
					return 0;
					//break;
			}
		}
	
	
	} 



	int result;
	int filecount = filepaths.size();

	std::vector<FILE*> files;

	for( int x=0; x < filecount; x++ )
	{
		FILE* fp = ::fopen( filepaths[x].c_str(), "rd" );
		if( fp != NULL )
			files.push_back(fp);
		else
		{
			fprintf( stderr, "Could not open \"%s\" for read.\n\n", filepaths[x].c_str() );
			return 1;
		}
	       		       
	}
	
	
	if( format == "s16" || format == "s16ne" )
	{
		short data[64]; 
		short sample;

		std::vector< short[64] > filedata(filecount);

		do {
			
			for( int d=0; d < filecount; d++ )
			{
				result = fread( &filedata[d], sizeof( filedata[d] ), 1, files[d] );
				if( result == 0 )
					return 0;
			}


			for( int i=0; i < 64; i++ ) {
				sample=0;
				for( int f=0; f < filecount; f++ )
				{
					sample += ( filedata[f][i] / filecount );
				}
				data[i] = sample; 
			}
			fwrite( &data, sizeof(data), 1, stdout );
		} while( result != 0 );
	}
	else if( format == "float32" || format == "float" || format == "" )
	{
	}

	return 0;
}

