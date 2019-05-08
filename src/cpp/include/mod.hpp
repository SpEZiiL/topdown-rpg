// src/cpp/mod.hpp
/*
 * Meta declarations for the embedded Python module.
 * 
 * Since: 2019-02-15
 * LastEdit: 2019-02-21
 */

#ifndef H2A8ACBE6_3126_4752_AB45_58BADF420507
#define H2A8ACBE6_3126_4752_AB45_58BADF420507

#include <Python.h>
#include <structmember.h>

#define EMB_MOD_NAME "game"
#define EMB_MOD_DOC \
	"Embedded Python Module for the text-adventure"

namespace game {
	inline namespace py {

		extern PyMethodDef EmbMethods[];
		extern PyModuleDef EmbModule;
		PyObject* PyInit_emb();

	}

}

#endif
