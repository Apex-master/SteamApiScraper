bool steam_item_scraper = 1;
bool buff_item_scraper = 1;

const ImVec4 active = ImColor(0, 100, 200, 255);
const ImVec4 inactive = ImColor(31, 30, 31, 255);

ImVec4 color_green = ImColor(34, 139, 34, 255); // Darker green
ImVec4 color_red = ImColor(178, 34, 34, 255);   // Darker red

const char* proxy_type_options[] = { "Rotating Proxies", "Proxy List" };


void CreateLogWindows(int numWindows, int numColumns)
{
    float columnWidth = ImGui::GetWindowContentRegionWidth() / numColumns;
    int currentColumn = 0;

    for (int i = 0; i < numWindows; ++i)
    {
        if (currentColumn > 0)
            ImGui::SameLine(0, ImGui::GetStyle().ItemSpacing.x);

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.34f, 0.34f, 0.34f, 1.0f));
        ImGui::BeginChild(("Log Window " + std::to_string(i)).c_str(), ImVec2(columnWidth, 150)); // Adjust size as needed

        // Use a unique identifier for each TextEditor widget
        std::string editorID = "##threadwindow" + std::to_string(i);
        text_editors[i].Render(editorID.c_str(), ImVec2(-1, -1));
        text_editors[i].SetPalette(TextEditor::GetDarkPalette());
        ImGui::PopStyleColor();

        ImGui::EndChild();

        if (currentColumn < numColumns - 1)
            currentColumn++;
        else
            currentColumn = 0;
    }
}



void RenderApplication(HWND hwnd)
{
    // Get the dimensions of the CreateWindow window
    RECT windowRect;
    GetClientRect(hwnd, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    // Set the size and position of the ImGui window
    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetNextWindowPos(ImVec2(windowWidth / 2, windowHeight / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("Steamie", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    ImGui::BeginChild("Controls", ImVec2(101.0f, ImGui::GetWindowHeight() - 69.0f), true);
    {
        DrawMaterialSeparator("Steam", 0);

        ImGui::PushStyleColor(ImGuiCol_Button, aiStyle == 1 ? active : inactive);
        if (ImGui::Button(ICON_FA_PAGER, ImVec2(100 - 15, 41)))
        {
            int total_items;

            if (steam_ids.GetAllSteamItemIDS())
            {
                logEditor.InsertText("[+] Obtained all item ids\n");

                std::thread t([&]() {
                    steam_ids.PrintAllSteamItems();
                });
                t.detach();
                
                //steam_all.SaveJsonToFile("test.json");
                if (steam_ids.ExtractDataFromJson(total_items))
                {
                    std::ostringstream oss;
                    oss << "[+] Total items: " << total_items << "\n";

                    // Get the concatenated string
                    std::string temp = oss.str();
                    logEditor.InsertText(temp);
                }
                
            }
            else
            {
                logEditor.InsertText("[-] Failed to obtain all steam items");
            }

        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Get all Steam item ids");
        }

        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Button, steam_item_scraper == 0 ? color_green : color_red);
        if (ImGui::Button(steam_item_scraper ? ICON_FA_PLAY : ICON_FA_STOP, ImVec2(100 - 15, 41)))
        {
            steam_item_scraper = !steam_item_scraper; // Toggle the state between true and false.
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Start Steam items scraper");
        }

        ImGui::PopStyleColor(2);
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 10);
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("steam-market-getter", ImVec2(windowWidth - 410.0f, ImGui::GetWindowHeight() - 69.0f), true);
    {
        DrawMaterialSeparator("Threads", 2);

        ImGui::Spacing();

        

        ImGui::BeginChild("threads", ImVec2(ImGui::GetWindowWidth() - 18.0f, ImGui::GetWindowHeight() - 104.0f), true);
        {
            CreateLogWindows(total_threads, 3);
        }
        ImGui::EndChild();

        float availableHeight = ImGui::GetContentRegionAvail().y;
        float childWindowHeight = 39.0f;
        float childWindowPosY = ImGui::GetCursorPosY() + availableHeight - childWindowHeight;

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.14f, 0.14f, 0.14f, 1.0f));

        ImGui::SetCursorPosY(childWindowPosY);
        ImGui::BeginChild("CurrentItem", ImVec2(ImGui::GetWindowWidth() - 18.0f, childWindowHeight), true);
        {
            ImVec2 textSize = ImGui::CalcTextSize(current_item.c_str());
            AlignForWidth(textSize.x);
            ImGui::Text(current_item.c_str());
        }   ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("Misc", ImVec2(280.0f, ImGui::GetWindowHeight() - 69.0f), true);
    {
        ImGui::PushItemWidth((120.0f));

        DrawMaterialSeparator("Settings", 1);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::BeginChild("SettingsWindow", ImVec2(ImGui::GetWindowWidth() - 18.0f, 289.0f), true);
        {
            ImGui::InputInt("Threads", &total_threads);
            ImGui::InputInt("Sleep", &total_sleep);
            ImGui::Combo("Proxies", &proxy_type_index, proxy_type_options, IM_ARRAYSIZE(proxy_type_options));

            if (proxy_type_index == 0)
            {
                static char address_buffer[256] = "127.0.0.01";
                ImGui::InputText("Address", address_buffer, sizeof(address_buffer));

                static char port_buffer[256] = "8080";
                ImGui::InputText("Port", port_buffer, sizeof(port_buffer));

                static char username_buffer[256] = "odijw1Dk1gn";
                ImGui::InputText("Username", username_buffer, sizeof(username_buffer));
                
                static char password_buffer[256] = "u5hg4hs6d1vy1g2bafl";
                ImGui::InputText("Password", password_buffer, sizeof(password_buffer));
            }
            else
            {
                static char proxy_list[256] = "IP:PORT";
                ImGui::InputTextMultiline("List", proxy_list, sizeof(proxy_list));
            }
        } ImGui::EndChild();

        ImGui::Spacing();

        DrawMaterialSeparator("Logs", 1);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::BeginChild("logwindow", ImVec2(ImGui::GetWindowWidth() - 18.0f, 304.0f), true);
        {
            logEditor.Render("##LogEditor", ImVec2(-1, -1));
            logEditor.SetShowWhitespaces(false);
            logEditor.SetReadOnly(true);
            logEditor.SetPalette(TextEditor::GetDarkPalette());
        } ImGui::EndChild();
        ImGui::PopStyleColor();



    }   ImGui::EndChild();

    ImGui::BeginChild("ProgressBar", ImVec2(ImGui::GetWindowWidth() - 18.0f, 49.0f), true);
    {
        ImGui::ProgressBar(progress, ImVec2(ImGui::GetWindowWidth() - 18.0f, 0.0f));
    }
    


    ImGui::End();
}