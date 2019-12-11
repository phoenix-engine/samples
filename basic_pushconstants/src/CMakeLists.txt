project(BasicPushConstants CXX C)

set(main_SRCS
  pushconst/pushconst.cxx
  main.cxx
)

add_executable(${APP_NAME} ${GUI_TYPE} ${main_SRCS})

target_include_directories(${APP_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/pushconst
)

if(NOT(APPLE))
  target_link_libraries(${APP_NAME}
	Phoenix
	SDL2main
	Consumer
	Error
	SDLUtil
	SDLWindow
	SDLScene
	SDLVKRenderer
	SDLInput
  )
else()
  target_link_libraries(${APP_NAME} Phoenix)
endif(NOT(APPLE))

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
