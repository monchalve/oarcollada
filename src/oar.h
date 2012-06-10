/*

	Defines the in-memory representation of the OAR format for easy access
	of elements.
	
*/
#include <vector>
#include <string>
#include <dirent.h> 

using namespace std;

typedef vector<string> OARDirectory;

class OAR {
public:

	OAR(const char *path);
	
	inline const OARDirectory objects() { return _objects; }
	inline const OARDirectory assets() { return _assets; }
	inline const OARDirectory landdata() { return _landdata; }
	inline const OARDirectory settings() { return _settings; }
	inline const OARDirectory terrains() { return _terrains; }
	
	
private:	

	char *_path;
    OARDirectory _objects;
    OARDirectory _assets;
    OARDirectory _landdata;
    OARDirectory _settings;
    OARDirectory _terrains;

	void _pushItems(struct dirent *dir, OARDirectory &directoryStore);
	
};