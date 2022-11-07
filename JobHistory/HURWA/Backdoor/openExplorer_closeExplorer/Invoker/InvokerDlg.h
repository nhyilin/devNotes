
// InvokerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CInvokerDlg �Ի���
class CInvokerDlg : public CDialogEx
{
// ����
public:
	CInvokerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_INVOKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	bool m_isOpened;
	bool m_isPwdRight;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
