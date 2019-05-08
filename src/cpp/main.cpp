// src/cpp/main.cpp
/*
 * Main C++ source file that calls the starting Python script.
 * 
 * Since: 2019-02-15
 * LastEdit: 2019-02-21
 */

#include <util/logger.hpp>
#include <util/utils.hpp>
#include <mod.hpp>
#include <os.hpp>

#define ASSETS_DIR_NAME  "assets"
#define SCRIPTS_DIR_NAME "python"
#define INIT_SCRIPT_NAME "init.py"
#define MAIN_SCRIPT_NAME "ui.py"

#if DEPLOY == 1
#define ASSETS_DIR  ASSETS_DIR_NAME
#define SCRIPTS_DIR SCRIPTS_DIR_NAME
#else
#define ASSETS_DIR  ".."  OS_FS_STR                 ASSETS_DIR_NAME
#define SCRIPTS_DIR ".."  OS_FS_STR  "src"  OS_FS_STR  SCRIPTS_DIR_NAME
#endif
#define INIT_SCRIPT SCRIPTS_DIR  OS_FS_STR  INIT_SCRIPT_NAME
#define MAIN_SCRIPT SCRIPTS_DIR  OS_FS_STR  MAIN_SCRIPT_NAME

using namespace game::util;

int main(int argc, char** argv) {
	logger err(std::cerr, false);

	// parsing arguments
	bool debug_clr = false;
	bool debug = false;
	switch(argc) {
	default: {
		char* basename = mbasename(argv[0]);
		err << basename << ": too many arguments\n"
				"usage: " << basename << " [debug_mode [debug_color]]"
				<< std::endl;
		free(basename);
		exit(-1);
		break;
	}
	case 3:
		debug_clr = istrue(argv[2]);
	case 2:
		debug = istrue(argv[1]);
	case 1:
		if(!debug && debug_clr) {
			char* basename = mbasename(argv[0]);
			err << basename << ": debug color requires debug mode" << std::endl;
			free(basename);
			exit(-1);
		}
		break;
	case 0:
		exit(-1); // should never happen
		break;
	}

	class null_streambuf : public std::streambuf {
	};
	null_streambuf null_streambuf;
	std::ostream null_ostream(&null_streambuf);
	logger debg(debug ? std::cout : null_ostream, debug_clr);

	debg << mnp::bold << mnp::fg_b_blue << "\n~~~ Debugging state active ~~~\n"
			<< mnp::endl;

	// application paths
	std::string exe_path,
			root_path,
			assets_path,
			scripts_path,
			init_script_path,
			main_script_path;
	{
		char *rel_exe_path = argv[0],
				*rel_root_path = mdirname(rel_exe_path),
				*rel_assets_path = strmcat(rel_root_path, OS_FS_STR ASSETS_DIR),
				*rel_scripts_path = strmcat(rel_root_path,
				OS_FS_STR SCRIPTS_DIR);

		char *abs_exe_path = abspath(rel_exe_path),
				*abs_root_path = abspath(rel_root_path),
				*abs_assets_path = abspath(rel_assets_path),
				*abs_scripts_path = abspath(rel_scripts_path);

		exe_path = std::string(abs_exe_path);
		root_path = std::string(abs_root_path);
		assets_path = std::string(abs_assets_path);
		scripts_path = std::string(abs_scripts_path);
		init_script_path = scripts_path + OS_FS_STR INIT_SCRIPT_NAME;
		main_script_path = scripts_path + OS_FS_STR MAIN_SCRIPT_NAME;

		free(abs_scripts_path);
		free(abs_assets_path);
		free(abs_root_path);
		free(abs_exe_path);
		free(rel_scripts_path);
		free(rel_assets_path);
		free(rel_root_path);
	}

	debg << mnp::fg_green << "Application paths:\n" << mnp::fg_yellow << ""
			"  exe path:         \"" << exe_path << "\"\n"
			"  root path:        \"" << root_path << "\"\n"
			"  assets path:      \"" << assets_path << "\"\n"
			"  scripts path:     \"" << scripts_path << "\"\n"
			"  init script path: \"" << init_script_path << "\"\n"
			"  main script path: \"" << main_script_path << "\"\n"
			<< mnp::endl;

	// init script
	std::string init;
	init = init + "import game\n"
			+ "game.exe_path = '" + exe_path + "'\n"
			+ "game.root_path = '" + root_path + "'\n"
			+ "game.assets_path = '" + assets_path + "'\n"
			+ "game.scripts_path = '" + scripts_path + "'\n"
			+ "game.debug = " + (debug ? "True" : "False") + '\n'
			+ "game.os = '" OS_STR "'\n"
			+ "del game\n";

	debg << mnp::fg_blue << "Initializing embedded interpreter...\n"
			<< mnp::endl;

	// embedded interpreter initializing
	wchar_t* program = Py_DecodeLocale(argv[0], NULL);
	if(program == NULL) {
		err << "Cannot decode argv[0]" << std::endl;
		exit(-1);
	}
	Py_SetProgramName(program);
	PyImport_AppendInittab(EMB_MOD_NAME, &game::py::PyInit_emb);
	Py_Initialize();

	// embedded script
	debg << mnp::fg_cyan << "Running embedded script:\n" << mnp::reset << init
			<< mnp::endl;
	PyRun_SimpleString(init.c_str());

	// init script file
	debg << mnp::fg_cyan << "Calling init script file \"" << init_script_path
			<< "\"\n" << mnp::endl;
	FILE *init_script = fopen(init_script_path.c_str(), "r");
	PyRun_SimpleFile(init_script, init_script_path.c_str());
	fclose(init_script);

	// main script file
	debg << mnp::fg_cyan << "Calling main script file \"" << main_script_path
			<< "\"\n" << mnp::endl;
	FILE* main_script = fopen(main_script_path.c_str(), "r");
	PyRun_SimpleFile(main_script, main_script_path.c_str());
	fclose(main_script);

	// test script file
	if(debug) {
		std::string test_script_path = scripts_path + OS_FS_STR "init.py";
		debg << mnp::fg_cyan << "Calling test script file \""
				<< test_script_path << "\"\n" << mnp::endl;
		FILE* test_script = fopen(test_script_path.c_str(), "r");
		PyRun_SimpleFile(test_script, test_script_path.c_str());
		fclose(test_script);
	}

	debg << mnp::fg_blue << "\nFinalizing embedded interpreter..."
			<< mnp::endl;
	Py_Finalize();
	PyMem_RawFree(program);
}
