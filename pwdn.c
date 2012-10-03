/*
 * Copyright (c) 2008-09, Stuart Colville
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, 
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *     * Neither the name of the Muffin Research Labs nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 * 		without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.  
 *
 * pwdn is a simple program to return n directories of the current working 
 * directory
 * 
 * Usage: 
 *     pwdn [numdirs]
 *
 * To compile:
 *     gcc pwdn.c -o <path-to-bin>
 *
 * Changelog:
 *     25th September 2009:
 *       - Fix for empty output when cwd is "/".
 *       - Fix for 0 passed in. 
 *
 * VERSION: 0.2
 *
 */
 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


main(int argc, char** argv)
{     
    long size;
    char *buf;
    char *ptr;                          
    char delim[]="/";
    char *token;
    int numdir = argv[1] ? atoi(argv[1]) : 2;
   
    // Fix for 0 passed in
    if (numdir <= 0){
        numdir = 1;
    }

    // get current working directory
    size = pathconf(".", _PC_PATH_MAX);
    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);        
    
    if (ptr == "/"){
        printf("/");
        return 0;
    }
 
    // count instances of slash
    int count=0;    
    char *slash = delim;     
    while (*ptr != '\0'){
        if(*ptr == *slash){
            count++;
        }
        ptr++;
    }
    
    // Get tokens based on slash split 
    int tokcount = 0;
    token = strtok(buf,delim);    
    if (count > numdir){
       printf("..."); 
    }

    // If we are at /
    if (token == NULL && count == 1){
        printf("/");
    }
    
    while (token != NULL)
    {        
      tokcount++;
      if (tokcount > count - numdir) {
          printf ("/%s", token);
      }
      token = strtok (NULL,delim);
    }                 
        
    printf("\n");
    free(buf);              
    return 0;
}
