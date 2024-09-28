use std::env;
use std::env::VarError;
use std::io::{Error, ErrorKind};
use std::path::PathBuf;

fn get_current_working_dir() -> std::io::Result<PathBuf> {
    env::current_dir()
}

// Initially passed by the top-level CMakeLists.txt to control which version
// of the static library of CBMC we were linking against. Staying in order to
// allow users to be able to easily change the version of the CBMC static
// library that's being looked up.
fn get_cbmc_version() -> Result<String, VarError> {
    env::var("CBMC_VERSION")
}

// Initially passed by the top-level CMakeLists.txt to control where the static
// library we link against was located. Now staying for backward compatibility of
// the build system, and to allow fine grained control for a user as to where the
// static library is located (be it in a build folder or a system `/lib` folder).
fn get_lib_directory() -> Result<String, VarError> {
    env::var("CBMC_LIB_DIR")
}

fn get_library_build_dir() -> std::io::Result<PathBuf> {
    let env_var_fetch_result = get_lib_directory();
    if let Ok(build_dir) = env_var_fetch_result {
        let mut path = PathBuf::new();
        path.push(build_dir);
        return Ok(path);
    }
    Err(Error::new(
        ErrorKind::Other,
        "Environment variable `CBMC_LIB_DIR' not set",
    ))
}

// This is needed so that cargo can find the include folder for the C++
// API headers at compile time.
fn get_include_directory_envvar() -> Result<String, VarError> {
    env::var("CBMC_INCLUDE_DIR")
}

fn get_include_directory() -> std::io::Result<PathBuf> {
    let env_var_fetch_result = get_include_directory_envvar();
    if let Ok(build_dir) = env_var_fetch_result {
        let mut path = PathBuf::new();
        path.push(build_dir);
        return Ok(path);
    }
    Err(Error::new(
        ErrorKind::Other,
        "Environment variable `CBMC_INCLUDE_DIR' not set",
    ))
}

fn main() {
    let cpp_api_include_path = match get_include_directory() {
        Ok(path) => path,
        Err(err) => {
            let error_message = &format!(
                "Error: {}.\n Advice: {}.",
                err,
                "Please set the environment variable `CBMC_INCLUDE_DIR' with the path that contains cprover/api.h on your system"
            );
            panic!("{}", error_message);
        }
    };

    let _build = cxx_build::bridge("src/lib.rs")
        .include(cpp_api_include_path)
        .include(get_current_working_dir().unwrap())
        .file("src/c_api.cc")
        .flag_if_supported("-std=c++17")
        .compile("cprover-rust-api");

    println!("cargo:rerun-if-changed=src/c_api.cc");
    println!("cargo:rerun-if-changed=include/c_api.h");

    let libraries_path = match get_library_build_dir() {
        Ok(path) => path,
        Err(err) => {
            let error_message = &format!(
                "Error: {}.\n Advice: {}.",
                err,
                "Please set the environment variable `CBMC_LIB_DIR' with the path that contains libcprover.x.y.z.a on your system"
            );
            panic!("{}", error_message);
        }
    };

    println!(
        "cargo:rustc-link-search=native={}",
        libraries_path.display()
    );

    let cprover_static_libname = match get_cbmc_version() {
        Ok(version) => String::from("cprover.") + &version,
        Err(_) => {
            let error_message = &format!(
                "Error: {}.\n Advice: {}.",
                "Environment variable `CBMC_VERSION' not set",
                "Please set the environment variable `CBMC_VERSION' with the version of CBMC you want to link against (e.g. 5.78.0)"
            );
            panic!("{}", error_message);
        }
    };

    println!("cargo:rustc-link-lib=static={}", cprover_static_libname);
}
