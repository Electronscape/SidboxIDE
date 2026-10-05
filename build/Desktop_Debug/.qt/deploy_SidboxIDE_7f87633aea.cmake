include("/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/build/Desktop_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/SidboxIDE-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/build/Desktop_Debug/SidboxIDE"
    GENERATE_QT_CONF
)
