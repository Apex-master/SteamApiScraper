#include "globals.h"

/*
250 total proxies
22,000 total items
100,000 total request per day per ip
*/

//processedItemCount++;
std::mutex progressMutex;
void ItemsScraper()
{
    while (true)
    {
        if (!steam_item_scraper && steam_item_info.size() != 0)
        {
            logEditor.InsertText("[+] Starting to scrape all items for buy and sell prices\n");

            std::vector<std::thread> threads(total_threads);
            std::vector<SteamItemDetails> steam_items_instances(total_threads);

            bool suspended;

            int itemsProcessedByThread = 0; // Initialize items processed by this thread

            auto processItems = [&](int threadId)
            {
                for (size_t i = threadId; i < steam_item_info.size(); i += total_threads)
                {
                    current_item = steam_item_info[i].market_name;

                    if (steam_items_instances[threadId].ProcessSteamItem(steam_item_info[i], threadId))
                    {
                        

                        //text_editors[threadId].Delete();
                        //text_editors[threadId].SetText("");

                        //std::string final_output = "ID: " + std::to_string(steam_item_info[i].id) + "\n" + "Item Name: " + steam_item_info[i].market_name + "\n" + "Buy Price : " + steam_item_info[i].buy_price + "\n" + "Sell Price: " + steam_item_info[i].sell_price + "\n";

                        //text_editors[threadId].InsertText(final_output);
                        //text_editors[threadId].InsertText("-------------------------------------\n");
                        text_editors[threadId].InsertText("[+] Obtained Item: " + std::to_string(steam_item_info[i].id) + "\n");
                        //text_editors[threadId].InsertText("[+] Obtained Item \n");
#
                        {
                            itemsProcessedByThread++;
                            int totalItemsProcessed = processedItemCount + itemsProcessedByThread;
                            float overallProgress = static_cast<float>(totalItemsProcessed) / steam_item_info.size();

                            std::lock_guard<std::mutex> lock(progressMutex);
                            progress = overallProgress;
                        }

                        //std::cout << "Thread " << threadId << ": Current item: " << steam_item_info[i].market_name << "\n" << "Items processed: " << totalItemsProcessed << "\n" << std::endl;
                    }
                    
                    if (total_sleep > 0)
                    {
                        Sleep(total_sleep * 1000);
                    }

                    if (steam_item_scraper)
                    {
                        logEditor.InsertText("[-] Failed to obtain all items, terminated before completion\n");
                        suspended = true;
                        progress = 0.0f;
                        break;
                    }
                }
            };

            for (int i = 0; i < total_threads; ++i)
            {
                threads[i] = std::thread(processItems, i);
            }

            for (int i = 0; i < total_threads; ++i)
            {
                threads[i].join();
            }

            if (!suspended)
            {
                logEditor.InsertText("[+] All items successfully obtained\n");
            }
            
        }
        Sleep(100);
    }
}

int main()
{
    //ConnectSocket();

    std::thread scraper_thr(ItemsScraper);
    scraper_thr.detach();

      for (int i = 0; i < 1000; ++i) {

          TextEditor editor;
          text_editors.push_back(editor);
      }

    InitImgui();

    return 0;
}