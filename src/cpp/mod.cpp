// src/cpp/mod.cpp
/*
 * mod.hpp implementation.
 * Meta declarations for the embedded Python module.
 * 
 * Since: 2019-02-15
 * LastEdit: 2019-02-21
 */

#include <mod.hpp>

#define _unused __attribute__ ((unused))

namespace game {
	inline namespace py {

		PyObject* _test(_unused PyObject* mod, _unused PyObject* args) {
			/*PyMemberDef members[] = {
			 {
			 .name = "attr",
			 .type = T_INT,
			 .offset = 0,
			 .flags = 0,
			 .doc = "test attr"
			 }
			 };
			 */
			return Py_None;
		}

		PyMethodDef EmbMethods[] = {
			{"_test", _test, METH_VARARGS, "Testing method"},
			//{"func", NULL, METH_VARARGS, "doc"},
			{NULL, NULL, 0, NULL}
		};

		PyModuleDef EmbModule = {
			.m_base = PyModuleDef_HEAD_INIT,
			.m_name = EMB_MOD_NAME,
			.m_doc = EMB_MOD_DOC,
			.m_size = -1,
			.m_methods = EmbMethods,
			.m_slots = NULL,
			.m_traverse = NULL,
			.m_clear = NULL,
			.m_free = NULL
		};

		PyObject* PyInit_emb(void) {
			return PyModule_Create(&EmbModule);
		}

	}
}
