# Sidbox C compiler and shared SDK

The first SDK binding is `SBOS_CreateWindow()`. The example uses `#include "apis.h"` in both builds. SidboxIDE uses its SDK headers directly. On Sidbox, the include loads the API data from `tfcard:/dev/apicore/apis.bin`. The resulting applet calls the firmware's EBI window entry.

## Generate both files with F5

From this extracted folder, run the one-time backend update with your existing SidboxIDE source folder. Use the folder containing `idelibs` and `development`.

```bash
./enable-f5-apicore.sh "/path/to/SidboxIDE"
```

The script builds the updated `idelibs/tools/bin/cgarm-build` from your local source and saves the prior executable as `cgarm-build.before-apicore`. The existing IDE window can use the updated backend on the next F5.

Open `compiler/compiler.proj` and press **F5**. The project builds `compiler/compiler.app` and `compiler/apis.bin` together using the same SDK. The project enables API export through `-DSIDC_EXPORT_APICORE` in its compiler flags.

The source patch is `ide/cgarm-build-apicore.patch`. To retain this feature in future full IDE builds, apply that patch to the SidboxIDE source tree before rebuilding the IDE.

## Build and test on Sidbox

1. Copy `compiler/compiler.app` to `/sidbox/c/compiler` on the TF card with the extension removed.
2. Copy `compiler/apis.bin` to `/dev/apicore/apis.bin` on the TF card.
3. Copy `examples/sdk-window/sdk-window.c` to a folder on the TF card. In the Sidbox shell, go to that folder and run these commands.

```text
compiler sdk-window.c
launch sdk-window.app
```

Look for a window titled **Hello from Sidbox SDK**. To edit the same file on Sidbox, use `compiler -e sdk-window.c` and press **Build** in the editor.

## Build the same example in the IDE

Open `examples/sdk-window/sdk-window.proj` and press **F5**. It builds the same `sdk-window.c` beside the project. Both projects use the GUI Applet V2 build.

The first binding supports `NULL` or `0` for the optional window-handle pointer, a string literal for the title, and the SDK's `SBX_WIN_DEFAULT` flag. The compiler also accepts the SDK entry signature `int main(int argc, char **argv)`. The existing C subset can use `argc`. Accessing `argv` elements requires pointer support.

## Export the SDK data from the terminal

For a standalone export, pass the path to the installed SDK directory containing `api/apis.h`.

```bash
./rebuild-apicore.sh /path/to/SidboxIDE/idelibs
```

The script reads the EBI table layout and constants from the SDK headers and writes `compiler/apis.bin`. The compiler validates the file format and checksum before using it.

| File | What it does |
| --- | --- |
| `compiler/export_apicore.c` | Exports the window signature's argument types, EBI offsets, and default flags. |
| `compiler/compiler.c` | `load_apicore()` reads the SDK data and `api_call()` emits native EBI calls. |
| `compiler/main.c` | `read_apicore()` reads the TF-card file through Sidbox's filesystem API. |

`examples/hello.c` is the original compiler test. Its `sidbox_message()` call uses the bundled runtime in `compiler/generated_runtime.h`. To regenerate that runtime after editing `runtime/program_runtime.c`, run `./rebuild-runtime.sh /path/to/SidboxIDE/idelibs` and rebuild the compiler.

The F5 build backend produced the same compiler and API bytes as the version tested on the handheld.
