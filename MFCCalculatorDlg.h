
// MFCCalculatorDlg.h: 头文件
//

#pragma once


// CMFCCalculatorDlg 对话框
class CMFCCalculatorDlg : public CDialogEx
{
// 构造
public:
	CMFCCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	CString h1,h2,h3,h4;
	afx_msg void OnBn1();
	afx_msg void OnEnEdit();
	CEdit mEdit;
	afx_msg void OnBn2();
	afx_msg void OnBn3();
	afx_msg void OnBn4();
	afx_msg void OnBn5();
	afx_msg void OnBn6();
	afx_msg void OnBn7();
	afx_msg void OnBn8();
	afx_msg void OnBn9();
	afx_msg void OnBn0();
	afx_msg void OnBnCE();
	afx_msg void OnBnBacksp();
	afx_msg void OnBnLeft();
	afx_msg void OnBnRight();
	afx_msg void OnBnPoint();
	afx_msg void OnBnAdd();
	afx_msg void OnBnSub();
	afx_msg void OnBnMulti();
	afx_msg void OnBnDivid();
	afx_msg void OnBnEqual();
	CEdit mOut;
	afx_msg void OnEnChangeh();
};
