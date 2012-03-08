/* 
 * File:   dump_io.h
 * Author: Flynn / Victor Vigel Flores.
 *
 * Created on October 20, 2011, 3:15 PM
 */

/* Função dump_line
*  This function reads and dumps any remaining characters on the current input
*  line of a file.
* Essa função lê e despeja qualquer caracter que esteja na stream de entrada.
*/
void dump_line( FILE * fp ){
  int ch;

  while( (ch = fgetc(fp)) != EOF && ch != '\n' )
    /* sem corpo */;
  printf(" \n");
}

void str_format( char * str ){
	int i  = strlen(str) - 1;

	str[i] = '\0';
	
}
