


set(Resource_Files
	"SPExpert.rc"
	resource.h
	"../common/versiondef.h"
)
source_group("Resource Files" FILES ${Resource_Files})

# Translation files

SET(Resource_TS_FILES
    resource/i18n/hurwa_zh_CN.ts
)
source_group("Resource Files\\resource\\i18n" FILES ${Resource_TS_FILES})

# make qm in source dir instead of Build
set_source_files_properties(${Resource_TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/resource/i18n")

# refer to https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Build-Qt4-Software


set (FILES_TO_TRANSLATE )
file (GLOB_RECURSE  HEADER_FILES *.h *.hpp)
file (GLOB_RECURSE  CPP_FILES *.cpp)
file (GLOB_RECURSE  UI_FILES *.ui)
set (FILES_TO_TRANSLATE ${FILES_TO_TRANSLATE} ${CPP_FILES} ${UI_FILES} ${HEADER_FILES} )

# file (GLOB TRANSLATIONS_FILES translations/*.ts)

option (UPDATE_TRANSLATIONS "Update source translation *.ts")
if (UPDATE_TRANSLATIONS)
 qt5_create_translation(EXPERT_QM_FILES ${FILES_TO_TRANSLATE} ${Resource_TS_FILES})
 # clean obsolete messages when update
 # qt5_create_translation(EXPERT_QM_FILES ${FILES_TO_TRANSLATE} ${Resource_TS_FILES} OPTIONS -no-obsolete)
else (UPDATE_TRANSLATIONS)
  qt5_add_translation(EXPERT_QM_FILES ${Resource_TS_FILES})
endif (UPDATE_TRANSLATIONS)

#add_custom_target(update_ts DEPENDS ${Resource_TS_FILES} ${FILES_TO_TRANSLATE})
add_custom_target(translations_target DEPENDS ${EXPERT_QM_FILES})

# install(FILES ${QM_FILES} DESTINATION
# ${CMAKE_INSTALL_PREFIX}/translations)

# prevent the generated files from being deleted during make clean
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM true)



set(QRC_Files
    "res-2.qrc"
    "res-3.qrc"
    "res-4.qrc"
    "res.qrc"
    "res_cpr_l.qrc"
    "res_cpr_r.qrc"
    "res_cuttool_2t.qrc"
    "res_findback.qrc"
    "res_pointGuid.qrc"
    "res_pointGuid_R.qrc"
    "res_pos_l.qrc"
    "res_pos_r.qrc"
    "res_registrate.qrc"
    "resnav.qrc"
    "setting.qrc"
    "t_point-2.qrc"
    "t_point.qrc"
   #  ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc  
)
source_group("QRC Files" FILES ${QRC_Files})

set(Resource_Files__..__..__res__profile
    "../../res/profile/PCIE1810.xml"
)
source_group("Resource Files\\..\\..\\res\\profile" FILES ${Resource_Files__..__..__res__profile})

set(Resource_Files__resource
    "resource/style.css"
)
source_group("Resource Files\\resource" FILES ${Resource_Files__resource})


set(Resource_Files__resource__icon
    "resource/icon/3d.png"
    # "resource/icon/3d.svg"
  #  "resource/icon/AR.svg"
    "resource/icon/assistpoints.png"
  #  "resource/icon/AUp.svg"
  #  "resource/icon/Bone.svg"
  #  "resource/icon/BoneAndProsthesis.svg"
    "resource/icon/cd.svg"
    "resource/icon/checkbox_checked.png"
    "resource/icon/checkbox_checked_hover.png"
    "resource/icon/checkbox_checked_pressed.png"
    "resource/icon/checkbox_unchecked.png"
    "resource/icon/checkbox_unchecked_hover.png"
    "resource/icon/checkbox_unchecked_pressed.png"
    "resource/icon/checkbox_unvisible.png"
    "resource/icon/checkbox_visible.png"
    "resource/icon/ComboBoxHover.svg"
    "resource/icon/ComboBoxNormal.svg"
    "resource/icon/ComboBoxPressed.svg"
  #  "resource/icon/connect.png"
  #  "resource/icon/connect.svg"
    "resource/icon/connected.png"
  #  "resource/icon/connected.svg"
  #  "resource/icon/contract.svg"
  #  "resource/icon/coordinate.png"
    "resource/icon/copy.svg"
  #  "resource/icon/cube.svg"
    "resource/icon/delete.svg"
    "resource/icon/dia_hov.png"
    "resource/icon/dia_nor.png"
    "resource/icon/dia_pres.png"
    "resource/icon/disk_bg.png"
    "resource/icon/done.svg"
    "resource/icon/done_clear.svg"
  #  "resource/icon/edit.svg"
    "resource/icon/eraser.png"
 #   "resource/icon/expand.svg"
  #  "resource/icon/F.svg"
    "resource/icon/failed.png"
  #  "resource/icon/farend.svg"
    "resource/icon/femur.png"
  #  "resource/icon/femur.svg"
    "resource/icon/fileBrowse.png"
    "resource/icon/finishBG.png"
  #  "resource/icon/FT.svg"
    "resource/icon/home.png"
    "resource/icon/homeGroup.png"
    "resource/icon/homeHover.png"
    "resource/icon/homePress.png"
  #  "resource/icon/IDown.svg"
    "resource/icon/interpolate.svg"
    "resource/icon/intersection.png"
  #  "resource/icon/intersection.svg"
   # "resource/icon/item.svg"
   # "resource/icon/layer.png"
  #  "resource/icon/layer.svg"
    "resource/icon/left_btn.svg"
    "resource/icon/left_hover.svg"
    "resource/icon/left_pressed.svg"
    "resource/icon/leftCT.png"
 #   "resource/icon/lineAndPoints.svg"
 #   "resource/icon/Lleft.svg"
    "resource/icon/login_bg.jpg"
    "resource/icon/logo.png"
 #   "resource/icon/M.svg"
    "resource/icon/mask.png"
  #  "resource/icon/mask.svg"
    "resource/icon/MinusDis.svg"
    "resource/icon/MinusHover.svg"
    "resource/icon/MinusNormal.svg"
    "resource/icon/MinusPressed.svg"
 #   "resource/icon/MRight.svg"
    "resource/icon/nav_bg.jpg"
    "resource/icon/navigator.png"
    "resource/icon/navigator_disconnect.png"
    "resource/icon/navigator_moving.png"
    "resource/icon/net.svg"
    "resource/icon/new.svg"
    "resource/icon/open.png"
    "resource/icon/mask_import.svg"
    "resource/icon/mask_export.svg"
    "resource/icon/pass.png"
 #   "resource/icon/PDown.svg"
    "resource/icon/PenTool.png"
 #   "resource/icon/PLeft.svg"
    "resource/icon/PlusDis.svg"
    "resource/icon/PlusHover.svg"
    "resource/icon/PlusNormal.svg"
    "resource/icon/PlusPressed.svg"
    "resource/icon/pointguid.png"
    "resource/icon/ProsBg.jpg"
 #   "resource/icon/push_disabled.svg"
 #   "resource/icon/push_hover.svg"
 #   "resource/icon/push_normal.svg"
 #   "resource/icon/push_pressed.svg"
    "resource/icon/radiobutton_checked.png"
    "resource/icon/radiobutton_checked_hover.png"
    "resource/icon/radiobutton_checked_pressed.png"
    "resource/icon/radiobutton_unchecked.png"
    "resource/icon/radiobutton_unchecked_hover.png"
    "resource/icon/radiobutton_unchecked_pressed.png"
    "resource/icon/redo.svg"
    "resource/icon/reset.svg"
 #   "resource/icon/ResetView.svg"
    "resource/icon/restView.png"
    "resource/icon/right_btn.svg"
    "resource/icon/right_hover.svg"
    "resource/icon/right_pressed.svg"
    "resource/icon/rightCT.png"
    "resource/icon/robotic_arm.svg"
    "resource/icon/robotic_arm_dis.svg"
#    "resource/icon/robotic_arm_move.svg"
 #   "resource/icon/save.svg"
    "resource/icon/saw_disabled.png"
    "resource/icon/saw_enabled.png"
    "resource/icon/saw_running.png"
    "resource/icon/sc_bg.png"
 #   "resource/icon/setting.svg"
 #   "resource/icon/sharp_probe.svg"
 #   "resource/icon/sheet.svg"
    "resource/icon/show_forceline.svg"
 #   "resource/icon/SHUN.svg"
 #   "resource/icon/shutdown.svg"
 #   "resource/icon/SUp.svg"
 #   "resource/icon/T.svg"
 #   "resource/icon/threshold.svg"
    "resource/icon/threshold_img.png"
    "resource/icon/tibia.png"
 #   "resource/icon/tibia.svg"
    "resource/icon/tibiaforceline.png"
  #  "resource/icon/tibiaforceline.svg"
  #  "resource/icon/tzBg.jpg"
    "resource/icon/undo.svg"
    "resource/icon/usb.svg"
    "resource/icon/zoomIn.svg"
    "resource/icon/zoomOut.svg"
)
source_group("Resource Files\\resource\\icon" FILES ${Resource_Files__resource__icon})

set(Resource_Files__resource__icon__cut
    "resource/icon/cut/cutstep_femur.svg"
    "resource/icon/cut/cutstep_standby.svg"
    "resource/icon/cut/cutstep_tibia.svg"
    "resource/icon/cut/pedal.svg"
    "resource/icon/cut/pedal_highlight.svg"
    "resource/icon/cut/offset-limit-normal.png"
    "resource/icon/cut/offset-limit-strict.png"
    "resource/icon/cut/auxfunction.png"
)
source_group("Resource Files\\resource\\icon\\cut" FILES ${Resource_Files__resource__icon__cut})

set(Resource_Files__resource__icon__dialog
    "resource/icon/dialog/close.png"
    "resource/icon/dialog/close_hover.png"
    "resource/icon/dialog/critical.png"
    "resource/icon/dialog/information.png"
    "resource/icon/dialog/lose_pressed.png"
    "resource/icon/dialog/warning.png"
)
source_group("Resource Files\\resource\\icon\\dialog" FILES ${Resource_Files__resource__icon__dialog})

set(Resource_Files__resource__icon__lamps
 #   "resource/icon/lamps/lam_F_Forbidden.svg"
 #   "resource/icon/lamps/lamp_base_Forbidden.svg"
 #   "resource/icon/lamps/lamp_blunt_tip_Forbidden.svg"
    "resource/icon/lamps/lamp_checkpoint_Hover.png"
    "resource/icon/lamps/lamp_checkpoint_Hover.svg"
    "resource/icon/lamps/lamp_checkpoint_Normal.png"
    "resource/icon/lamps/lamp_checkpoint_Normal.svg"
    "resource/icon/lamps/lamp_checkpoint_Pressed.png"
    "resource/icon/lamps/lamp_checkpoint_Pressed.svg"
    "resource/icon/lamps/lamp_femur.svg"
    "resource/icon/lamps/lamp_flange.svg"
 #   "resource/icon/lamps/lamp_Flange_Forbidden.svg"
    "resource/icon/lamps/lamp_sharp_tip.svg"
 #   "resource/icon/lamps/lamp_sharp_tip_Forbidden.svg"
 #   "resource/icon/lamps/lamp_T_Forbidden.svg"
    "resource/icon/lamps/lamp_tibia.svg"
)
source_group("Resource Files\\resource\\icon\\lamps" FILES ${Resource_Files__resource__icon__lamps})

set(Resource_Files__resource__icon__manage
    "resource/icon/manage/Delete.svg"
    "resource/icon/manage/DeleteDisabled.svg"
    "resource/icon/manage/Export.svg"
    "resource/icon/manage/newUser.svg"
    "resource/icon/manage/newUserDisabled.svg"
    "resource/icon/manage/proExport.svg"
    "resource/icon/manage/report.png"
    "resource/icon/manage/Reset.svg"
    "resource/icon/manage/Reset_hover.svg"
    "resource/icon/manage/Reset_pre.svg"
    "resource/icon/manage/Search.svg"
    "resource/icon/manage/Search_hover.svg"
    "resource/icon/manage/Search_pre.svg"
    "resource/icon/manage/uerMgrBg.png"
    "resource/icon/manage/userEdit.svg"
    "resource/icon/manage/userEditDisabled.svg"
)
source_group("Resource Files\\resource\\icon\\manage" FILES ${Resource_Files__resource__icon__manage})

set(Resource_Files__resource__icon__plan
    "resource/icon/plan/alignmentNormal.png"
    "resource/icon/plan/BoneAndProsthesisNormal.png"
    "resource/icon/plan/BoneNormal.png"
    "resource/icon/plan/DownIHover.svg"
    "resource/icon/plan/DownINormal.svg"
    "resource/icon/plan/DownIPressed.svg"
    "resource/icon/plan/DownPHover.svg"
    "resource/icon/plan/DownPNormal.svg"
    "resource/icon/plan/DownPPressed.svg"
    "resource/icon/plan/Far-endNormal.png"
    "resource/icon/plan/FNormal.png"
    "resource/icon/plan/forcelineNormal.png"
    "resource/icon/plan/LeftLHover.svg"
    "resource/icon/plan/LeftLNormal.svg"
    "resource/icon/plan/LeftLPressed.svg"
    "resource/icon/plan/LeftMHover.svg"
    "resource/icon/plan/LeftMNormal.svg"
    "resource/icon/plan/LeftMPressed.svg"
    "resource/icon/plan/LeftPHover.svg"
    "resource/icon/plan/LeftPNormal.svg"
    "resource/icon/plan/LeftPPressed.svg"
    "resource/icon/plan/LTurnHover.svg"
    "resource/icon/plan/LTurnNormal.svg"
    "resource/icon/plan/LTurnPressed.svg"
    "resource/icon/plan/OsteotomyAndProsthesisNormal.png"
    "resource/icon/plan/OsteotomyNormal.png"
    "resource/icon/plan/parallelNormal.png"
    "resource/icon/plan/RightAHover.svg"
    "resource/icon/plan/RightANormal.svg"
    "resource/icon/plan/RightAPressed.svg"
    "resource/icon/plan/RightLHover.svg"
    "resource/icon/plan/RightLNormal.svg"
    "resource/icon/plan/RightLPressed.svg"
    "resource/icon/plan/RightMHover.svg"
    "resource/icon/plan/RightMNormal.svg"
    "resource/icon/plan/RightMPressed.svg"
    "resource/icon/plan/RTurnHover.svg"
    "resource/icon/plan/RTurnNormal.svg"
    "resource/icon/plan/RTurnPressed.svg"
    "resource/icon/plan/SixKnifeNormal.png"
    "resource/icon/plan/TNormal.png"
    "resource/icon/plan/UpAHover.svg"
    "resource/icon/plan/UpANormal.svg"
    "resource/icon/plan/UpAPressed.svg"
    "resource/icon/plan/UpSHover.svg"
    "resource/icon/plan/UpSNormal.svg"
    "resource/icon/plan/UpSPressed.svg"
)
source_group("Resource Files\\resource\\icon\\plan" FILES ${Resource_Files__resource__icon__plan})

set(Resource_Files__resource__icon__pointguid
    "resource/icon/pointguid/femurPointsVisible.png"
    "resource/icon/pointguid/pointGuid-1.png"
    "resource/icon/pointguid/pointGuid-10.png"
    "resource/icon/pointguid/pointGuid-11.png"
    "resource/icon/pointguid/pointGuid-12.png"
    "resource/icon/pointguid/pointGuid-13.png"
    "resource/icon/pointguid/pointGuid-14.png"
    "resource/icon/pointguid/pointGuid-15.png"
    "resource/icon/pointguid/pointGuid-16.png"
    "resource/icon/pointguid/pointGuid-17.png"
    "resource/icon/pointguid/pointGuid-2.png"
    "resource/icon/pointguid/pointGuid-26.png"
    "resource/icon/pointguid/pointGuid-27.png"
    "resource/icon/pointguid/pointGuid-3.png"
    "resource/icon/pointguid/pointGuid-4.png"
    "resource/icon/pointguid/pointGuid-5.png"
    "resource/icon/pointguid/pointGuid-6.png"
    "resource/icon/pointguid/pointGuid-7.png"
    "resource/icon/pointguid/pointGuid-8.png"
    "resource/icon/pointguid/pointGuid-9.png"
    "resource/icon/pointguid/tibiaPointsVisible.png"
)
source_group("Resource Files\\resource\\icon\\pointguid" FILES ${Resource_Files__resource__icon__pointguid})

set(Resource_Files__resource__icon__pointguid-R
    "resource/icon/pointguid-R/pointGuid-R-1.png"
    "resource/icon/pointguid-R/pointGuid-R-10.png"
    "resource/icon/pointguid-R/pointGuid-R-11.png"
    "resource/icon/pointguid-R/pointGuid-R-12.png"
    "resource/icon/pointguid-R/pointGuid-R-13.png"
    "resource/icon/pointguid-R/pointGuid-R-14.png"
    "resource/icon/pointguid-R/pointGuid-R-15.png"
    "resource/icon/pointguid-R/pointGuid-R-16.png"
    "resource/icon/pointguid-R/pointGuid-R-17.png"
    "resource/icon/pointguid-R/pointGuid-R-2.png"
    "resource/icon/pointguid-R/pointGuid-R-26.png"
    "resource/icon/pointguid-R/pointGuid-R-27.png"
    "resource/icon/pointguid-R/pointGuid-R-3.png"
    "resource/icon/pointguid-R/pointGuid-R-4.png"
    "resource/icon/pointguid-R/pointGuid-R-5.png"
    "resource/icon/pointguid-R/pointGuid-R-6.png"
    "resource/icon/pointguid-R/pointGuid-R-7.png"
    "resource/icon/pointguid-R/pointGuid-R-8.png"
    "resource/icon/pointguid-R/pointGuid-R-9.png"
)
source_group("Resource Files\\resource\\icon\\pointguid-R" FILES ${Resource_Files__resource__icon__pointguid-R})

set(Resource_Files__resource__icon__pointverify
    "resource/icon/pointverify/femur_check_pt_verify.png"
    "resource/icon/pointverify/tibia_check_pt_verify.png"
)
source_group("Resource Files\\resource\\icon\\pointverify" FILES ${Resource_Files__resource__icon__pointverify})

set(Resource_Files__resource__icon__prepare
 #   "resource/icon/prepare/lleg_larm.png"
    "resource/icon/prepare/lleg_lateral_malleolus.jpg"
    "resource/icon/prepare/lleg_medial_malleolus.jpg"
 #   "resource/icon/prepare/lleg_rarm.png"
    "resource/icon/prepare/ndi_front.png"
    "resource/icon/prepare/ndi_side.png"
    "resource/icon/prepare/ndi_top.png"
    "resource/icon/prepare/rleg_lateral_malleolus.jpg"
    "resource/icon/prepare/rleg_medial_malleolus.jpg"
 #   "resource/icon/prepare/rleg_rarm.png"
)
source_group("Resource Files\\resource\\icon\\prepare" FILES ${Resource_Files__resource__icon__prepare})

set(Resource_Files__resource__icon__prepare__cprLeftLeg
    "resource/icon/prepare/cprLeftLeg/cpr_f_lleg_larm.png"
    "resource/icon/prepare/cprLeftLeg/cpr_f_lleg_rarm.png"
    "resource/icon/prepare/cprLeftLeg/cpr_t_lleg_larm.png"
    "resource/icon/prepare/cprLeftLeg/cpr_t_lleg_rarm.png"
)
source_group("Resource Files\\resource\\icon\\prepare\\cprLeftLeg" FILES ${Resource_Files__resource__icon__prepare__cprLeftLeg})

set(Resource_Files__resource__icon__prepare__cprRightLeg
    "resource/icon/prepare/cprRightLeg/cpr_f_rleg_larm.png"
    "resource/icon/prepare/cprRightLeg/cpr_f_rleg_rarm.png"
    "resource/icon/prepare/cprRightLeg/cpr_t_rleg_larm.png"
    "resource/icon/prepare/cprRightLeg/cpr_t_rleg_rarm.png"
)
source_group("Resource Files\\resource\\icon\\prepare\\cprRightLeg" FILES ${Resource_Files__resource__icon__prepare__cprRightLeg})

set(Resource_Files__resource__icon__prepare__cutTool_1
)
source_group("Resource Files\\resource\\icon\\prepare\\cutTool_1" FILES ${Resource_Files__resource__icon__prepare__cutTool_1})

set(Resource_Files__resource__icon__prepare__cutTool_2
)
source_group("Resource Files\\resource\\icon\\prepare\\cutTool_2" FILES ${Resource_Files__resource__icon__prepare__cutTool_2})

set(Resource_Files__resource__icon__prepare__left
)
source_group("Resource Files\\resource\\icon\\prepare\\left" FILES ${Resource_Files__resource__icon__prepare__left})

set(Resource_Files__resource__icon__prepare__posLeftLeg
    "resource/icon/prepare/posLeftLeg/pos_f_lleg_larm.png"
    "resource/icon/prepare/posLeftLeg/pos_f_lleg_rarm.png"
    "resource/icon/prepare/posLeftLeg/pos_t_lleg_larm.png"
    "resource/icon/prepare/posLeftLeg/pos_t_lleg_rarm.png"
)
source_group("Resource Files\\resource\\icon\\prepare\\posLeftLeg" FILES ${Resource_Files__resource__icon__prepare__posLeftLeg})

set(Resource_Files__resource__icon__prepare__posRightleg
    "resource/icon/prepare/posRightleg/pos_f_rleg_larm.png"
    "resource/icon/prepare/posRightleg/pos_f_rleg_rarm.png"
    "resource/icon/prepare/posRightleg/pos_t_rleg_larm.png"
    "resource/icon/prepare/posRightleg/pos_t_rleg_rarm.png"
)
source_group("Resource Files\\resource\\icon\\prepare\\posRightleg" FILES ${Resource_Files__resource__icon__prepare__posRightleg})

set(Resource_Files__resource__icon__prepare__right
)
source_group("Resource Files\\resource\\icon\\prepare\\right" FILES ${Resource_Files__resource__icon__prepare__right})

set(Resource_Files__resource__icon__registration
    "resource/icon/registration/BoxSelect.png"
    "resource/icon/registration/BoxSelect.svg"
    "resource/icon/registration/Cartilage.png"
    "resource/icon/registration/Clear.png"
    "resource/icon/registration/Clear.svg"
    "resource/icon/registration/Delete.png"
    "resource/icon/registration/Delete.svg"
    "resource/icon/registration/DeleteDisabled.svg"
    "resource/icon/registration/F-Point1.png"
    "resource/icon/registration/F-Point2.png"
    "resource/icon/registration/F-Point3.png"
    "resource/icon/registration/femur.png"
    "resource/icon/registration/Point.png"
    "resource/icon/registration/Registration.png"
    "resource/icon/registration/Reset.png"
    "resource/icon/registration/Reset.svg"
    "resource/icon/registration/RT.png"
    "resource/icon/registration/RT.svg"
    "resource/icon/registration/T-Point1.png"
    "resource/icon/registration/T-Point2.png"
)
source_group("Resource Files\\resource\\icon\\registration" FILES ${Resource_Files__resource__icon__registration})

set(Resource_Files__resource__icon__setting
    "resource/icon/setting/acctestDis.png"
    "resource/icon/setting/acctestHov.png"
    "resource/icon/setting/acctestNor.png"
    "resource/icon/setting/acctestPre.png"
    "resource/icon/setting/logmanDis.png"
    "resource/icon/setting/logmanHov.png"
    "resource/icon/setting/logmanNor.png"
    "resource/icon/setting/logmanPre.png"
    "resource/icon/setting/navmanDis.png"
    "resource/icon/setting/navmanHov.png"
    "resource/icon/setting/navmanNor.png"
    "resource/icon/setting/navmanPre.png"
    "resource/icon/setting/robotmanDis.png"
    "resource/icon/setting/robotmanHov.png"
    "resource/icon/setting/robotmanNor.png"
    "resource/icon/setting/robotmanPre.png"
    "resource/icon/setting/sysinfoDis.png"
    "resource/icon/setting/sysinfoHov.png"
    "resource/icon/setting/sysinfoNor.png"
    "resource/icon/setting/sysinfoPre.png"
    "resource/icon/setting/syssetDis.png"
    "resource/icon/setting/syssetHov.png"
    "resource/icon/setting/syssetNor.png"
    "resource/icon/setting/syssetPre.png"
)
source_group("Resource Files\\resource\\icon\\setting" FILES ${Resource_Files__resource__icon__setting})

set(Resource_Files__resource__icon__toolbutton
    "resource/icon/toolbutton/disabled.svg"
    "resource/icon/toolbutton/hover.svg"
    "resource/icon/toolbutton/normal.svg"
    "resource/icon/toolbutton/pressed.svg"
)
source_group("Resource Files\\resource\\icon\\toolbutton" FILES ${Resource_Files__resource__icon__toolbutton})



SET(ALL_RESOURCE_FILES 
	${Resource_Files}
	${QRC_Files}
  ${Resource_TS_FILES}
  ${EXPERT_QM_FILES}
	${Resource_Files__..__..__res__profile}
	${Resource_Files__resource}
    ${Resource_Files__resource__i18n}
    ${Resource_Files__resource__icon}
    ${Resource_Files__resource__icon__cut}
    ${Resource_Files__resource__icon__dialog}
    ${Resource_Files__resource__icon__lamps}
    ${Resource_Files__resource__icon__manage}
    ${Resource_Files__resource__icon__plan}
    ${Resource_Files__resource__icon__pointguid}
    ${Resource_Files__resource__icon__pointguid-R}
    ${Resource_Files__resource__icon__pointverify}
    ${Resource_Files__resource__icon__prepare}
    ${Resource_Files__resource__icon__prepare__cprLeftLeg} 
    ${Resource_Files__resource__icon__prepare__cprRightLeg}
    ${Resource_Files__resource__icon__prepare__cutTool_1}
    ${Resource_Files__resource__icon__prepare__cutTool_2}
    ${Resource_Files__resource__icon__prepare__left}
    ${Resource_Files__resource__icon__prepare__posLeftLeg}
	${Resource_Files__resource__icon__prepare__right}
	${Resource_Files__resource__icon__registration}
	${Resource_Files__resource__icon__setting}
	${Resource_Files__resource__icon__toolbutton}
)