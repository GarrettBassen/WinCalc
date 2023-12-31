#include "wincalc.h"
#include "ui_wincalc.h"

double calcValue = 0;

// Triggers
bool op_add     = false; // Add
bool op_sub     = false; // Subtract
bool op_mul     = false; // Multiply
bool op_div     = false; // Divide
bool op_mod     = false; // Modulo
bool ac_equ     = false; // Equals
bool ac_clr     = false; // Clear
bool ac_clr_e   = false; // Clear Entry
bool ac_back    = false; // Backspace
bool ac_inv     = false; // Inverse
bool ac_sign    = false; // Sign change

WinCalc::WinCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WinCalc)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(calcValue));

    // Initialize operand buttons
    QString name = "btn_operand_dot";
    QPushButton *numButtons[11];
    for (int i = 0; i < 11; ++i)
    {
        numButtons[i] = WinCalc::findChild<QPushButton *>(name);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(operand_pressed()));
        name = "btn_operand_" + QString::number(i);
    }

    // Initialize operator buttons
    connect(ui->btn_operator_add, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->btn_operator_sub, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->btn_operator_mul, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->btn_operator_div, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->btn_operator_mod, SIGNAL(released()), this, SLOT(operator_pressed()));

    // Initialize action buttons
    connect(ui->btn_action_clear, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_clear_entry, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_backspace, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_equals, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_inv, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_sign, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_sqrd, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_sqrt, SIGNAL(released()), this, SLOT(action_pressed()));
}

WinCalc::~WinCalc()
{
    delete ui;
}

void WinCalc::operand_pressed()
{
    QString displayStr = ui->display->text();
    QPushButton *btn = (QPushButton *)sender();

    if (displayStr == "0")
    {
        ui->display->setText(btn->text());
    }
    else
    {
        ui->display->setText(displayStr.append(btn->text()));
    }
}

void WinCalc::operator_pressed()
{
    QString op = ((QPushButton *)sender())->text();

    /*if (op.compare("+", Qt::CaseInsensitive))
    {

    }*/

    // TODO
    // +
    // -
    // *
    // /
    // %
}

void WinCalc::action_pressed()
{
    QString action = ((QPushButton *)sender())->text();

    if (action.compare("C", Qt::CaseInsensitive) == 0)
    {
        calcValue = 0;
        op_add     = false;
        op_sub     = false;
        op_mul     = false;
        op_div     = false;
        op_mod     = false;
        ac_equ     = false;
        ac_clr     = false;
        ac_clr_e   = false;
        ac_back    = false;
        ac_inv     = false;
        ac_sign    = false;
        ui->display->setText(QString::number(calcValue));
    }
    else if (action.compare("CE", Qt::CaseInsensitive) == 0)
    {
        ui->display->setText("");
    }
    else if (action.compare("←", Qt::CaseInsensitive) == 0)
    {
        QString currValue = ui->display->text();
        currValue.chop(1);
        currValue.isEmpty() ? ui->display->setText("0") : ui->display->setText(currValue);
    }

    // TODO
    // EQUALS SIGN
    // INV
    // SIGN CHANGE
    // SQUARED
    // SQUARE ROOT
}
