/****************************************************************************
Copyright (c) 2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "Cocos2dxLuaLoader.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
// testing
#include <dlfcn.h>

using namespace cocos2d;

extern "C"
{
    int loader_Lua_Android(lua_State *L)
    {
        std::string filename(luaL_gsub(L, luaL_checkstring(L, 1), ".", "/")); 
        filename.append(".lua");
        lua_remove(L, -1);

        CCLog("loader_Lua_Android: %s", filename.c_str());
        CCString* pFileContent = CCString::createWithContentsOfFile(filename.c_str());
        CCLog("loader_Lua_Android: %s %d", filename.c_str(), pFileContent->length());

        if (pFileContent)
        {
            if (luaL_loadstring(L, pFileContent->getCString()) != 0)
            {
                luaL_error(L, "error loading module %s from file %s :\n\t%s",
                    lua_tostring(L, 1), filename.c_str(), lua_tostring(L, -1));
            }
            CCLog("exits from loader_Lua_Android");
        }
        else
        {
            CCLog("can not get file data of %s", filename.c_str());
        }

        return 1;
    }

#if 0
    static const char *mkfuncname (lua_State *L, const char *modname) {
        const char *funcname;
        const char *mark = strchr(modname, *LUA_IGMARK);
        if (mark) modname = mark + 1;
        funcname = luaL_gsub(L, modname, ".", LUA_OFSEP);
        funcname = lua_pushfstring(L, POF"%s", funcname);
        lua_remove(L, -2);  /* remove 'gsub' result */
        return funcname;
    }

    static int ll_loadfunc (lua_State *L, const char *path, const char *sym) {
        void **reg = ll_register(L, path);
        if (*reg == NULL) *reg = ll_load(L, path);
        if (*reg == NULL)
            return ERRLIB;  /* unable to load library */
        else {
            lua_CFunction f = ll_sym(L, *reg, sym);
            if (f == NULL)
                return ERRFUNC;  /* unable to find function */
            lua_pushcfunction(L, f);
            return 0;  /* return function */
        }
    }

    static void **ll_register (lua_State *L, const char *path) {
        void **plib;
        lua_pushfstring(L, "%s%s", LIBPREFIX, path);
        lua_gettable(L, LUA_REGISTRYINDEX);  /* check library in registry? */
        if (!lua_isnil(L, -1))  /* is there an entry? */
            plib = (void **)lua_touserdata(L, -1);
        else {  /* no entry yet; create one */
            lua_pop(L, 1);
            plib = (void **)lua_newuserdata(L, sizeof(const void *));
            *plib = NULL;
            luaL_getmetatable(L, "_LOADLIB");
            lua_setmetatable(L, -2);
            lua_pushfstring(L, "%s%s", LIBPREFIX, path);
            lua_pushvalue(L, -2);
            lua_settable(L, LUA_REGISTRYINDEX);
        }
        return plib;
    }

    static void *ll_load (lua_State *L, const char *path) {
        void *lib = dlopen(path, RTLD_NOW);
        if (lib == NULL) lua_pushstring(L, dlerror());
        return lib;
    }

    static lua_CFunction ll_sym (lua_State *L, void *lib, const char *sym) {
        lua_CFunction f = (lua_CFunction)dlsym(lib, sym);
        if (f == NULL) lua_pushstring(L, dlerror());
        return f;
    }
    static const char *pushnexttemplate (lua_State *L, const char *path) {
        const char *l;
        while (*path == *LUA_PATHSEP) path++;  /* skip separators */
        if (*path == '\0') return NULL;  /* no more templates */
        l = strchr(path, *LUA_PATHSEP);  /* find next separator */
        if (l == NULL) l = path + strlen(path);
        lua_pushlstring(L, path, l - path);  /* template */
        return l;
    }


    static int readable (const char *filename) {
        FILE *f = fopen(filename, "r");  /* try to open file */
        if (f == NULL) return 0;  /* open failed */
        fclose(f);
        return 1;
    }


    static const char *findfile (lua_State *L, const char *name,
            const char *pname) {
        CCLog("findfile entered");
        const char *path;
        name = luaL_gsub(L, name, ".", LUA_DIRSEP);
        CCLog("name = %s", name);
        lua_getfield(L, LUA_ENVIRONINDEX, pname);
        path = lua_tostring(L, -1);
        CCLog("here?");
        if (path == NULL) {
            CCLog("path is null");
            // luaL_error(L, LUA_QL("package.%s") " must be a string", pname);
            return NULL;
        } else {
            CCLog(path);
        }
        lua_pushliteral(L, "");  /* error accumulator */
        CCLog("1");
        while ((path = pushnexttemplate(L, path)) != NULL) {
            const char *filename;
            filename = luaL_gsub(L, lua_tostring(L, -1), LUA_PATH_MARK, name);
            lua_remove(L, -2);  /* remove path template */
            CCLog("findfile %s", filename);
            if (readable(filename))  /* does file exist and is readable? */ {
                CCLog("3");
                return filename;  /* return that file name */
            }
            lua_pushfstring(L, "\n\tno file " LUA_QS, filename);
            lua_remove(L, -2);  /* remove file name */
            lua_concat(L, 2);  /* add entry to possible error message */
        }
        CCLog("2");
        return NULL;  /* not found */
    }
#endif
#if 0
    void mkDirAndCopySharedLib(std::string path, std::string filename) {
        path.append(filename);
        const char *pStr = path.c_str();
        CCLog("path = %s", pStr);
        const char *cur = pStr;
        char *p = NULL; 
        while ((p = strchr(cur, '/')) != NULL) {
            *p = '\0';
            CCLog("Checking dir %s", pStr);
            DIR *pDir = opendir(pStr);
            if (pDir == NULL) {
                if (mkdir(pStr, 0755) != 0)
                    CCLog("mkdir(%s) failed.", pStr);
            } else
                closedir(pDir);
            *p = '/'; 
            cur = p + 1;
        }

        CCLog("final pStr = %s", pStr);
        FILE *file = fopen(pStr, "w");
        if (!file) {
            CCLog("failed to fopen(%s)", pStr);
            return;
        }

        CCString* pFileContent = CCString::createWithContentsOfFile(filename.c_str());
        if (pFileContent)
            fwrite((void*)pFileContent->getCString(), pFileContent->length(), 1, file);
        else {
            CCLog("failed to read content from %s", filename.c_str());
        }
        fclose(file);
    }

    int loader_C_Android(lua_State *L)
    {
        std::string basename = CCFileUtils::sharedFileUtils()->getWriteablePath() + "lua/";
        std::string filename(luaL_checkstring(L, 1));
        CCLog("loader_C_Android: %s %s", basename.c_str(), filename.c_str());
        for (std::string::iterator it=filename.begin(); it<filename.end(); it++)
            if (*it == '.')
                *it = '/';
        filename.append(".so");
        CCLog("update filename: %s", filename.c_str());

        FILE *pFile = fopen((basename + filename).c_str(), "r");
        if (!pFile) {
            CCLog("failed to open file");
            mkDirAndCopySharedLib(basename, filename);
        } else {
            fclose(pFile);
        }

        const char * t = findfile(L, "socket.core", "path");
        if (t != NULL) CCLog(t);
        /* This part is used to dlopen and dlsym */
        CCLog("dlopen");
        void *lib = dlopen("/system/lib/libz.so", RTLD_NOW);
        CCLog("dlopen returned");
        if (lib == NULL) {
            CCLog("dlopen failed.");
            return 1;
        } else {
            CCLog("dlsym");
            lua_CFunction f = (lua_CFunction)dlsym(lib, "gzopen");
            CCLog("dlsym returned");
            if (f == NULL) {
                CCLog("dlsym failed.");
                return 1;
            }
        }
#if 0
        char *pathname = basename.append(filename).getCString();
        char *funcname = mkfuncname(L, luaL_checkstring(L, 1));
        if (ll_loadfunc(L, pathname, funcname) != 0)
            loaderror(L, pathname);
#endif
        CCLog("happy return");
        return 1;  /* library loaded successfully */
    }
#endif
}
