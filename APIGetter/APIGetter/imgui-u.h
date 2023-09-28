/*

Imgui Helpers

*/

static int aiStyle = 0;



ImVec2 operator+(const ImVec2& a, const ImVec2& b)
{
    return ImVec2(a.x + b.x, a.y + b.y);
}

void CreateHeader(const char* text)
{
    auto windowWidth = ImGui::GetWindowSize().x;
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize(text).x) * 0.5f);
    ImGui::Text(text);
    ImGui::Spacing();
    ImGui::Separator();
}

void AlignForWidth(float width, float alignment = 0.5f)
{
    ImGuiStyle& style = ImGui::GetStyle();
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
}


void DrawMaterialSeparator(const char* headerText, int col) {
    // Define the height of the separator
    const float separatorHeight = 4.0f;

    // Get the position and size of the window
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    // Calculate the position and width of the separator, accounting for scrolling
    ImVec2 separatorPos = ImGui::GetCursorScreenPos();  // Use screen position instead of window position
    separatorPos.y += ImGui::GetStyle().ItemSpacing.y + ImGui::GetTextLineHeight() + 4.0f;
    float separatorWidth = windowSize.x - ImGui::GetStyle().FramePadding.x * 2;

    // Define the colors based on the col value
    ImVec4 startColor;
    ImVec4 endColor;

    if (col == 0) {
        startColor = ImVec4(0.635f, 0.141f, 0.141f, 1.0f);
        endColor = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);
    }
    else if (col == 1) {
        startColor = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);
        endColor = ImVec4(0.635f, 0.141f, 0.141f, 1.0f);
    }
    else if (col == 2) {
        // Set the third color as a solid color (e.g., gray)
        startColor = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);
        endColor = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);
    }

    // Draw the separator with the specified colors
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor(
        separatorPos,
        ImVec2(separatorPos.x + separatorWidth, separatorPos.y + separatorHeight),
        ImGui::GetColorU32(startColor),
        ImGui::GetColorU32(endColor),
        ImGui::GetColorU32(endColor),
        ImGui::GetColorU32(startColor)
    );

    // Center the text and add the header text
    ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize(headerText).x) / 2);
    ImGui::Text(headerText);

    ImGui::Dummy(ImVec2(0, 10)); // Adds 10 units of vertical padding
}
void Theme()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

    style->WindowPadding = ImVec2(8, 8);
    style->FramePadding = ImVec2(4, 2);
    style->ItemSpacing = ImVec2(6, 4);
    style->ItemInnerSpacing = ImVec2(6, 4);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 18.0f;
    style->GrabMinSize = 14.0f;
    style->GrabRounding = 3.0f;
    style->WindowBorderSize = 0.0f;
    style->ChildBorderSize = 1.0f;
    style->PopupBorderSize = 1.0f;
    style->FrameBorderSize = 0.0f;
    style->WindowRounding = 4.0f;
    style->ChildRounding = 4.0f;
    style->FrameRounding = 4.0f;
    style->PopupRounding = 2.0f;
    style->ScrollbarRounding = 0.0f;
    style->GrabRounding = 2.0f;

    style->FramePadding = ImVec2(8, 6);

    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

    style->Colors[ImGuiCol_Border] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);

    style->Colors[ImGuiCol_SliderGrab] = ImColor(215, 37, 38, 255);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);

    style->Colors[ImGuiCol_Button] = ImVec4(0.635f, 0.141f, 0.141f, 1.0f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

    style->Colors[ImGuiCol_CheckMark] = ImColor(215, 37, 38, 255);;

    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);

    style->Colors[ImGuiCol_ChildBg] = ImColor(31, 30, 31, 255);

    style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(215, 37, 38, 255);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(195, 27, 18, 255);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.906f, 0.310f, 0.310f, 1.0f);

    style->Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);

    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.23f, 0.23f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.56f, 0.56f, 0.58f, 0.50f);

    style->Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.23f, 0.23f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 0.50f);

    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.52f, 0.88f, 0.35f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.52f, 0.88f, 0.50f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.52f, 0.88f, 0.67f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.52f, 0.88f, 0.95f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);

    // Change the color of the progress bar
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.635f, 0.141f, 0.141f, 1.0f); // Change this color as needed


}

