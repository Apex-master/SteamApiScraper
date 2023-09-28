int processedItemCount = 0; // Initialize the counter

struct buff_item
{
    float buy_price;
    float sell_price;
};

struct steam_item
{
    int id;
    std::string market_name;
    std::string name_id;
    std::string buy_price;
    std::string sell_price;
    buff_item buff_item;
};



std::vector<steam_item> steam_item_info; // market_name nameID

class SteamAllItemDetails
{
private:
    std::string response_data;

public:

    bool GetAllSteamItemIDS()
    {
        std::ifstream file("test.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            return false;
        }

        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        nlohmann::json json;
        try {
            json = nlohmann::json::parse(jsonStr);
        }
        catch (const nlohmann::json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            return 1;
        }

        // std::cout << json.dump(4) << std::endl;
        response_data = json.dump(4);
    }

    bool GetAllSteamItemsViaAPI() 
    {
        CURL* curl;
        CURLcode res;

        curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Error initializing libcurl." << std::endl;
            return false;
        }

        std::string api_url = "https://api.steamapis.com/market/items/730?api_key=4zcIK1VfG6UVWdER0zg0cf-mYBk";
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return false;
        }
        else {
            std::cout << "Successfully made API request to get all steam items" << std::endl;
            curl_easy_cleanup(curl);
            return true;
        }
    }

    void PrintAllSteamItems()
    {
        nlohmann::json json_response = nlohmann::json::parse(response_data);
        std::cout << "Response Data:" << std::endl;
        std::cout << json_response.dump(4) << std::endl;
    }

    void SaveJsonToFile(const std::string& filename) 
    {
        try 
        {
            nlohmann::json json_response = nlohmann::json::parse(response_data);
            std::ofstream file(filename);

            if (file.is_open()) 
            {

                file << json_response.dump(4);
                std::cout << "JSON data saved to " << filename << std::endl;
            }
            else 
            {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
        }
        catch (const nlohmann::json::exception& e) 
        {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        }
    }

    bool ExtractDataFromJson(int& total_items)
    {
        try 
        {
            steam_item_info.clear();

            nlohmann::json json_response = nlohmann::json::parse(response_data);
            int id_counter = 1;
            if (json_response.contains("data") && json_response["data"].is_array()) 
            {
                const auto& data_array = json_response["data"];

                for (const auto& item : data_array) 
                {
                    if (item.is_object() && item.contains("market_name") && !item["market_name"].is_null() &&
                        item.contains("nameID") && !item["nameID"].is_null()) 
                    {

                        std::string market_name = item["market_name"].get<std::string>();
                        std::string nameID = item["nameID"].get<std::string>();

                        steam_item item;
                        item.id = id_counter++;
                        item.market_name = market_name;
                        item.name_id = nameID;


                        steam_item_info.push_back(item);

                    }
                    else 
                    {
                        std::cerr << "Skipping item due to missing or null fields." << std::endl;
                    }
                }
            }
            else 
            {
                std::cerr << "JSON response is missing the 'data' array." << std::endl;
                return false;
            }
            total_items = steam_item_info.size();
            return true;
        }
        catch (const nlohmann::json::exception& e) 
        {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            return false;
        }
    }

    void PrintPhasedSteamItems()
    {
        for (const auto& item : steam_item_info) 
        {
            std::cout << "Market Name: " << item.market_name << std::endl;
            std::cout << "NameID: " << item.name_id << std::endl;
            std::cout << "--------------------------" << std::endl;
        }
    }

}; SteamAllItemDetails steam_ids;

//  "http://85.199.229.156:7492",
//  "http://199.228.220:7300",

std::vector<std::string> proxy_list = 
{
    "http://119.42.36.201:6101",
    "http://64.137.106.6:6499",
    "http://206.41.172.47:6607",
    "http://38.170.157.147:9186",
    "http://104.239.37.176:5828",
    "http://107.179.51.217:5860",
    "http://193.42.225.57:6548",

    "http://166.88.195.154:6159",
    "http://154.30.251.118:5259",
    "http://193.36.172.213:6296",
    "http://150.107.225.198:6463",
    "http://38.153.135.253:5633",
    "http://38.154.206.238:9729",
    "http://136.0.109.222:5816",

    "http://216.74.80.33:6605",
    "http://45.250.64.174:5811",
    "http://104.239.90.19:6410",
    "http://136.0.88.237:6530",
    "http://147.185.250.103:6889",
    "http://206.41.179.52:5728",
    "http://38.154.194.41:9454",

    "http://147.185.217.56:6490",
    "http://184.174.126.237:6529",
    "http://104.239.37.35:5687",
    "http://136.0.88.119:6412",
    "http://64.137.37.26:6616",
    "http://38.170.157.70:9109",
    "http://45.250.67.113:6660",

    "http://206.41.175.181:6394",
    "http://209.242.204.74:5815",
    "http://45.251.61.62:6780",
    "http://103.99.33.237:6232",
    "http://104.223.175.232:6268",
    "http://147.185.250.47:6833",
    "http://136.0.207.184:6133",

    "http://38.154.197.17:6683",
    "http://194.116.249.236:6087",
    "http://104.223.175.201:6237",
    "http://45.43.84.46:6671",
    "http://45.131.94.230:6217",
    "http://38.170.157.113:9152",
    "http://171.22.248.158:6050",

    "http://206.41.179.15:5691",
    "http://166.88.224.194:6823",
    "http://103.101.88.156:5880",
    "http://142.111.1.43:6534",
    "http://23.94.138.75:6349",
    "http://166.88.3.191:6543",
    "http://134.73.69.7:5997",
    "http://104.239.19.124:6801",
};

std::vector<std::string> proxy_list10free =
{
    "http://185.199.231.45:8382",
    "http://188.74.210.207:6286",
    "http://188.74.183.10:8279",
    "http://188.74.210.21:6100",
    "http://45.155.68.129:8133",
    "http://154.95.36.199:6893",
    "http://45.94.47.66:8110",

};
std::mutex proxy_mutex;
size_t current_proxy_index = 0;

std::string proxy_addr = "http://p.webshare.io:80";
std::string proxy_auth = "jkakrvxh-rotate:1ti8rf4usa7k";
std::string proxy_auth2 = "obxuakgn-rotate:u54dvy2gbafl";

class SteamItemDetails
{
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
    {
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    CURL* curl;
    curl_slist* headers;

    int maxRetries = 5;
    int retryDelaySec = 1;

public:
    SteamItemDetails()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize libcurl globally
        curl = curl_easy_init();
        if (!curl)
        {
            throw std::runtime_error("Error initializing curl!");
        }

        headers = nullptr;
        headers = curl_slist_append(headers, "Host: steamcommunity.com");
        headers = curl_slist_append(headers, "Connection: keep-alive");
        headers = curl_slist_append(headers, "Accept: */*");
        //headers = curl_slist_append(headers, "Cookie: timezoneOffset=3600,0; browserid=2806357411733183453; Steam_Language=english; steamLoginSecure=76561198319970456||eyAidHlwIjogIkpXVCIsICJhbGciOiAiRWREU0EiIH0.eyAiaXNzIjogInI6MEQyQV8yMkEwMURGMV9DQUQyOSIsICJzdWIiOiAiNzY1NjExOTgzMTk5NzA0NTYiLCAiYXVkIjogWyAiY2xpZW50IiwgIndlYiIgXSwgImV4cCI6IDE2OTQ0NTU5MDcsICJuYmYiOiAxNjg1NzI4NjMwLCAiaWF0IjogMTY5NDM2ODYzMCwgImp0aSI6ICIwRDFBXzIzMjJBRjU5X0FBRDBDIiwgIm9hdCI6IDE2ODU1NDI3NTUsICJydF9leHAiOiAxNzAzNzEwNzU3LCAicGVyIjogMCwgImlwX3N1YmplY3QiOiAiODEuMTUzLjE5My4xODUiLCAiaXBfY29uZmlybWVyIjogIjgxLjE1My4xOTMuMTg1IiB9.AlaEVtHBuf-RqEBkqGy2xmj1p-qUWUQ7UN_rR4y30VWuzFIhAcSLsuyoTmyLxNqjJNohU6feaxe-AWfekphtDw; clientsessionid=2f9a322ae7274524; sessionid=e0f47775d64a06df088ac9e8; steamCountry=NL%7Cea44c97e44e8c665d423b9e65519d3b1; webTradeEligibility=%7B%22allowed%22%3A1%2C%22allowed_at_time%22%3A0%2C%22steamguard_required_days%22%3A15%2C%22new_device_cooldown_days%22%3A0%2C%22time_checked%22%3A1694368637%7D");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; Valve Steam Client/default/1690583737) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.121 Safari/537.36");
        headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");
        headers = curl_slist_append(headers, "Sec-Fetch-Site: same-origin");
        headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
        headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
        headers = curl_slist_append(headers, "Referer: https://steamcommunity.com/market/listings/730/AK-47%20%7C%20Nightwish%20%28Field-Tested%29");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
        headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.9,en-GB;q=0.8");
        headers = curl_slist_append(headers, "If-Modified-Since: Sun, 10 Sep 2023 17:58:40 GMT");
        headers = curl_slist_append(headers, "content-length: 0");
    }

    ~SteamItemDetails()
    {
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        curl_global_cleanup();
    }


    bool SendRequest(const std::string& api_url, std::string& response, int threadId)
    {
        for (int i = 0; i < maxRetries; i++)
        {
            if (i > 0)
            {
                std::this_thread::sleep_for(std::chrono::seconds(retryDelaySec));
                //std::cout << "Retry Attempt: " << i << std::endl;
                std::string full1 = "[-] Retry Attempt: " + std::to_string(i) + "\n";

                text_editors[threadId].InsertText(full1);
            }

            std::string proxy;

            if (proxy_type_index == 0)
            {
                proxy = proxy_addr;
            }
            else
            {
                {
                    std::lock_guard<std::mutex> lock(proxy_mutex);
                    proxy = proxy_list[current_proxy_index];
                    std::cout << proxy << std::endl;

                    if (current_proxy_index == proxy_list.size() - 1)
                    {
                        current_proxy_index = 0;
                    }
                    else
                    {
                        current_proxy_index++;
                    }
                }
            }
            curl_easy_setopt(curl, CURLOPT_PROXY, proxy.c_str());
            curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxy_auth.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");

            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK)
            {
                //curl_easy_cleanup(curl); // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY
                //curl = curl_easy_init(); // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY

                text_editors[threadId].InsertText("[-] curl_easy_perform() failed \n");
                continue; // Retry
            }

            long http_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            if (http_code != 200)
            {
                std::string full = "HTTP Error: " + std::to_string(http_code) + " Request failed\n";

                text_editors[threadId].InsertText(full);

                curl_easy_cleanup(curl); // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY
                curl = curl_easy_init(); // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY

                //std::cerr << "HTTP Error " << http_code << ": Request failed" << std::endl;
                continue; // Retry
            }

            if (!response.empty())
            {
                //curl_easy_cleanup(curl);  // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY
                //curl = curl_easy_init();  // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY

                return true; // Success
            }
            else
            {
                //std::cerr << "Empty response data received." << std::endl;
                text_editors[threadId].InsertText("[-] Empty response data received. \n");

                //curl_easy_cleanup(curl); // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY
                //curl = curl_easy_init(); // REMOVE THESE TO KEEP CONNECTION WITH WORKING PROXY

                continue; // Retry
            }
        }

        curl_easy_cleanup(curl);
        curl = curl_easy_init();

        return false; // All retries failed
    }

    // add stop once finished
    // change current item text to finished
    // add log for finished
    // add time to each thread log
    // add top header for http status code for each thread box

    bool ProcessSteamItem(steam_item& item, int threadId)
    {
        std::string response;
        std::string api_url = "https://steamcommunity.com/market/itemordershistogram?country=GB&language=english&currency=2&item_nameid=" + item.name_id + "&two_factor=0";

        try
        {
            bool success = SendRequest(api_url, response, threadId);

            if (success)
            {
                nlohmann::json json_response = nlohmann::json::parse(response);

                if (json_response.contains("buy_order_graph"))
                {
                    const auto& buy_order_graph = json_response["buy_order_graph"];
                    if (!buy_order_graph.empty())
                    {
                        const auto& top_buy_order = buy_order_graph[0];
                        double buy_price = top_buy_order[0].get<double>();
                        item.buy_price = std::to_string(buy_price);
                    }
                }

                if (json_response.contains("sell_order_graph"))
                {
                    const auto& sell_order_graph = json_response["sell_order_graph"];
                    if (!sell_order_graph.empty())
                    {
                        const auto& top_sell_order = sell_order_graph[0];
                        double sell_price = top_sell_order[0].get<double>();
                        item.sell_price = std::to_string(sell_price);
                    }
                }

                return true;
            }
            else
            {
                text_editors[threadId].InsertText("[-] Failed to retrieve data for item: " + item.market_name + " ID: " + item.name_id + "\n");
                return false;
            }
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "[-] JSON parsing error: " << e.what() << std::endl;
        }

        return false;
    }
};
