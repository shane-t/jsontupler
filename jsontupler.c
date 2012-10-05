#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1

void ask ( char* text, char* input_buffer ) {
    fputs( text, stdout );
    fflush( stdout );
    fgets( input_buffer, sizeof input_buffer, stdin );

    if ( input_buffer[strlen( input_buffer ) - 1] == '\n' ) {
        input_buffer[strlen( input_buffer ) - 1] = '\0';
    }
}

int main ( int argc, char* argv[] ) {

    FILE * fp;
    int newfile = false;
    int answered;
    int finalize;
    int first;
    int count = 0;
    char input [120];
    char input2 [120];
    char buffer [245];

    if ( argc < 2 ) {
        printf( "Usage: %s [output filename]\n", argv[0] );
        exit(0);
    }

    fp = fopen( argv[1], "r");

    if ( fp == NULL ) {
        fputs( "- creating new file.\n", stdout );
        newfile = true;
    } else {
        fclose(fp);
    }

    fp = fopen( argv[1], "a+" );
    
    if ( newfile ) {
        fputs( "- beginning JSON\n", stdout );
        fwrite("[\n", 1, 1, fp);
        first = true;
    } else {
        first = false;
    }

    for (;;) {

        memset( buffer, 0, sizeof buffer );

        if ( first ) {
            //not first anymore, next time, there's a comma
            first = false;
            strcat( buffer, "  " );
        } else {
            strcat( buffer, "  ," );
        }

        ask ( "Key?> ", input );
        
        // outta here

        if ( strcmp( input, "END" ) == 0 ) {
            fputs( "Written to disk\n", stdout );
            fflush( stdout );
            break;
        }

        strcat( buffer, " { \"" );
        strcat( buffer, input );
        strcat( buffer, "\": " );

        ask ( "Value?> ", input2 );

        strcat( buffer, " \"" );
        strcat( buffer, input2 );
        strcat( buffer, "\" }\n" );

        fputs( buffer, stdout );
        fputs( buffer, fp );
    }

    answered = false;

    do {
        fputs( "Finalize? (Y/N)> ", stdout );
        fflush( stdout );

        fgets( input, sizeof input, stdin );

        if ( input[0] == 'Y' ) {
            answered = true;
            finalize = true;
        } else if (input[0] == 'N' ) {
            answered = true;
            finalize = false;
        }

    } while ( answered == false );

    if ( finalize ) {
        fputs( "Finalizing...\n", stdout );
        fwrite( "]", 1, 1, fp );
    } else {
        fputs(  "Not Finalizing\n", stdout );
    }

    fclose( fp );
    return 0;
}

