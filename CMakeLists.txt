project(SDL_GUI)

# set(CMAKE_CXX_STANDARD 17)
set(SDL2_INCLUDE_DIR C:/SDL2/include)
set(SDL2_LIB_DIR C:/SDL2/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

link_libraries(SDL2 SDL2_ttf SDL2_image)
include_directories(include Radiobutton Textbox Theme Dropdown Slider Checkbox Button Window Widget Parent Utils Text Frame Label Entry EventHandler)
add_executable(SDL_GUI main.cpp include/text_handling.cpp Radiobutton/Radiobutton.cpp Radiobutton/Radiobutton.hpp Textbox/Textbox.cpp Textbox/Textbox.hpp Theme/Theme.cpp Theme/Theme.hpp Dropdown/Dropdown.cpp Dropdown/Dropdown.hpp Slider/Slider.cpp Slider/Slider.hpp Checkbox/Checkbox.cpp Checkbox/Checkbox.hpp EventHandler/EventHandler.cpp EventHandler/EventHandler.hpp Button/Button.cpp Button/Button.hpp Entry/Entry.cpp Entry/Entry.hpp Frame/Frame.cpp Frame/Frame.hpp Label/Label.cpp Label/Label.hpp Parent/Parent.cpp Parent/Parent.hpp Rect/Rect.cpp Rect/Rect.hpp Text/Text.cpp Text/Text.hpp Utils/Utils.hpp Widget/Widget.cpp Widget/Widget.hpp Window/Window.cpp Window/Window.hpp "SDL_GUI.hpp" "EventHandler/EventHandler.cpp" "EventHandler/EventHandler.hpp" "Checkbox/Checkbox.hpp" "Checkbox/Checkbox.cpp" "Slider/SliderInt.cpp" "Slider/SliderInt.hpp" "Slider/SliderFloat.hpp" "Slider/SliderFloat.cpp")
