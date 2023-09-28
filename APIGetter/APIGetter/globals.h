#include <curl\curl.h>

#include <iostream>
#include <fstream>
#include <future>

#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>

int total_threads = 2;
int total_sleep = 0;
float progress = 0.0f;
std::string current_item = {};
int proxy_type_index = 0;

#include "text_editor.h"

std::vector<TextEditor> text_editors;
static TextEditor logEditor, test1;
std::mutex textEditorsMutex;

#include "socket.io/sio_client.h"
using namespace sio;














#include "json.h"
#include "helper.h"
#include "steam_tasks.h"
#include "init_imgui.h"




