
// MFCCalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCCalculator.h"
#include "MFCCalculatorDlg.h"
#include "afxdialogex.h"
#include "Calcul.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCalculatorDlg 对话框


CMFCCalculatorDlg::CMFCCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDC_EDIT8, mOut);
	DDX_Text(pDX, edit_h, h1);
	DDX_Text(pDX, edit_h2, h2);
	DDX_Text(pDX, edit_h3, h3);
	DDX_Text(pDX, edit_h4, h4);

}

BEGIN_MESSAGE_MAP(CMFCCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON29, &CMFCCalculatorDlg::OnBn1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCCalculatorDlg::OnEnEdit)
	ON_BN_CLICKED(IDC_BUTTON30, &CMFCCalculatorDlg::OnBn2)
	ON_BN_CLICKED(IDC_BUTTON31, &CMFCCalculatorDlg::OnBn3)
	ON_BN_CLICKED(IDC_BUTTON25, &CMFCCalculatorDlg::OnBn4)
	ON_BN_CLICKED(IDC_BUTTON26, &CMFCCalculatorDlg::OnBn5)
	ON_BN_CLICKED(IDC_BUTTON27, &CMFCCalculatorDlg::OnBn6)
	ON_BN_CLICKED(IDC_BUTTON21, &CMFCCalculatorDlg::OnBn7)
	ON_BN_CLICKED(IDC_BUTTON22, &CMFCCalculatorDlg::OnBn8)
	ON_BN_CLICKED(IDC_BUTTON23, &CMFCCalculatorDlg::OnBn9)
	ON_BN_CLICKED(IDC_BUTTON34, &CMFCCalculatorDlg::OnBn0)
	ON_BN_CLICKED(IDC_BUTTON19, &CMFCCalculatorDlg::OnBnCE)
	ON_BN_CLICKED(IDC_BUTTON20, &CMFCCalculatorDlg::OnBnBacksp)
	ON_BN_CLICKED(IDC_BUTTON17, &CMFCCalculatorDlg::OnBnLeft)
	ON_BN_CLICKED(IDC_BUTTON18, &CMFCCalculatorDlg::OnBnRight)
	ON_BN_CLICKED(IDC_BUTTON33, &CMFCCalculatorDlg::OnBnPoint)
	ON_BN_CLICKED(IDC_BUTTON24, &CMFCCalculatorDlg::OnBnAdd)
	ON_BN_CLICKED(IDC_BUTTON28, &CMFCCalculatorDlg::OnBnSub)
	ON_BN_CLICKED(IDC_BUTTON32, &CMFCCalculatorDlg::OnBnMulti)
	ON_BN_CLICKED(IDC_BUTTON35, &CMFCCalculatorDlg::OnBnDivid)
	ON_BN_CLICKED(IDC_BUTTON36, &CMFCCalculatorDlg::OnBnEqual)
	ON_EN_CHANGE(edit_h, &CMFCCalculatorDlg::OnEnChangeh)
END_MESSAGE_MAP()


// CMFCCalculatorDlg 消息处理程序

BOOL CMFCCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCalculatorDlg::OnEnEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCCalculatorDlg::OnBn0()
{
	// 数字“0”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("0");
	mEdit.SetWindowText(str);
}

void CMFCCalculatorDlg::OnBn1()
{
	// 数字“1”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("1");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn2()
{
	// 数字“2”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("2");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn3()
{
	// 数字“3”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("3");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn4()
{
	// 数字“4”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("4");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn5()
{
	// 数字“5”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("5");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn6()
{
	// 数字“6”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("6");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn7()
{
	// 数字“7”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("7");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn8()
{
	// 数字“8”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("8");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBn9()
{
	// 数字“9”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("9");
	mEdit.SetWindowText(str);

}


void CMFCCalculatorDlg::OnBnCE()
{
	// “清屏”按钮
	mEdit.SetWindowText(_T(""));
}


void CMFCCalculatorDlg::OnBnBacksp()
{
	// “后退”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str.Left(str.GetLength() - 1);
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnLeft()
{
	// “左括号”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("(");
	mEdit.SetWindowText(str);
	//mOut.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnRight()
{
	// “右括号”按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T(")");
	mEdit.SetWindowText(str);
	//mOut.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnPoint()
{
	// "."按钮
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T(".");
	mEdit.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnAdd()
{
	// 加号
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("+");
	mEdit.SetWindowText(str);
	//mOut.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnSub()
{
	// 减号
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("-");
	mEdit.SetWindowText(str);
	//mOut.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnMulti()
{
	// 乘号
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("*");
	mEdit.SetWindowText(str);
	//mOut.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnDivid()
{
	// 除号
	CString str;
	mEdit.GetWindowText(str);
	str = str + _T("/");
	mEdit.SetWindowText(str);
	//mOut.SetWindowText(str);
}


void CMFCCalculatorDlg::OnBnEqual()
{
	// 等号
	CString str;
	mEdit.GetWindowText(str);
	mOut.SetWindowText(str);
	CT2CA pszConvertedAnsiString(str); 
	string exp_str(pszConvertedAnsiString); 

	//将算式连同结果输出到历史记录框
	CString str1;
	str1 = str;
	str1 = str1 + _T("=");
	//mOut.SetWindowText(str1);

	if (exp_str != "")
	{
		Calcul e(exp_str);
		if (e.test())
		{
			string tmp;
			stringstream ss;
			ss << e.calculate();
			ss >> tmp;
			str = tmp.c_str();
		}
		else
		{
			str = "输入错误";
		}
		mEdit.SetWindowText(str);
		mOut.SetWindowText(str1+str);
		h4 = h3;
		h3 = h2;
		h2 = h1;
		h1 = str1 + str;
		UpdateData(FALSE);

		
	}
}


void CMFCCalculatorDlg::OnEnChangeh()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
