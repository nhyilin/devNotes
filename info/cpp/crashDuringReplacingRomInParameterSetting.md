[步骤]
在工程师账号下或管理员账号下点击【设置】按钮，点击【参数设置】，在ROM文件替换页面 或 探针参数设置页面点击【替换rom文件】/【替换探针文件】按钮，在没有外部设置插入的情况下点击【导入】按钮

[结果]
程序闪退

[期望]
程序不闪退，应有提示对话框





判断硬盘:m_storageWidget->selectedDrive()


if (m_storageWidget->selectedDrive().isNull()) {
    RMessageBox::information(this, QStringLiteral("探针参数"), QStringLiteral("请先插入U盘！"));
    qInfo() << "[yilin] Please insert a USB drever!";
    return;