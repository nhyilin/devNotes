
// InvokerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CInvokerDlg 对话框
class CInvokerDlg : public CDialogEx
{
// 构造
public:
	CInvokerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INVOKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	bool m_isOpened;
	bool m_isPwdRight;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReboot();
	afx_msg void OnBnClickedBtnOpenexplorer();
	afx_msg void OnBnClickedBtnremoveexplorer();
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	CButton m_btnOpenExplorer;
	CButton btn_repairExplorer;
	CEdit m_editPwd;
	CButton m_btnCheck;
	afx_msg void OnBnClickedPwdCheck();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
