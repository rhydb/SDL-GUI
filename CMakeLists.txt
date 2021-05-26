project(SDL_GUI)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/SDL2/include)
set(SDL2_LIB_DIR C:/SDL2/lib/x64)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

link_libraries(SDL2 SDL2_ttf SDL2_image)
include_directories(Button Window Widget Parent Utils Text Frame Label Entry)
add_executable(SDL_GUI main.cpp Button/Button.cpp Button/Button.hpp Entry/Entry.cpp Entry/Entry.hpp Frame/Frame.cpp Frame/Frame.hpp Label/Label.cpp Label/Label.hpp Parent/Parent.cpp Parent/Parent.hpp Rect/Rect.cpp Rect/Rect.hpp Text/Text.cpp Text/Text.hpp Utils/Utils.hpp Widget/Widget.cpp Widget/Widget.hpp Window/Window.cpp Window/Window.hpp)