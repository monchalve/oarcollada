#include "oar.h"
#include <string.h>
#include <unistd.h> 
#include <iostream>

using namespace std;

OAR::OAR(const char* path) {
	
	_path = strdup(path);
	
	// Open the file at path, and list all elements each of the folders
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
	chdir(path);
    if (d == NULL)
        return;
	
	while( (dir = readdir(d)) ) {

	    if( strcmp(dir->d_name, "assets" ) == 0) {
            _pushItems(dir, _assets);
        } else if (strcmp(dir->d_name, "objects") == 0) {
            _pushItems(dir, _objects);
        } else if (strcmp(dir->d_name, "settings") == 0) {
            _pushItems(dir, _settings);
        } else if (strcmp(dir->d_name, "landdata") == 0) {
            _pushItems(dir, _landdata);
        } else if (strcmp(dir->d_name, "terrains") == 0) {
            _pushItems(dir, _terrains);
        }
               
	}
}


void OAR::_pushItems(struct dirent *dir, OARDirectory &directoryStore) {
    
    DIR *d;
    struct dirent *subdir;
    d = opendir(dir->d_name);
    
    if (d == NULL)
        return;
    
    while( (subdir = readdir(d)) ) { 
		if( strcmp( subdir->d_name, "." ) == 0 || 
		  	strcmp( subdir->d_name, ".." ) == 0 ) {
				continue;
		}

		directoryStore.push_back(string(_path) + dir->d_name + "/" + string(subdir->d_name));
    } 
    
}
