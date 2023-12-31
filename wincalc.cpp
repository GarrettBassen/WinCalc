#include "wincalc.h"
#include "ui_wincalc.h"
#include <cmath>

// Values
double calcValue    = 0;
double buffOperand  = 0;

// Special buttons
bool override = false;

// Triggers
bool op_add     = false; // Add
bool op_sub     = false; // Subtract
bool op_mul     = false; // Multiply
bool op_div     = false; // Divide
bool op_mod     = false; // Modulo

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
    connect(ui->btn_action_clear_entry, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_backspace, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_inv, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_sign, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_sqrd, SIGNAL(released()), this, SLOT(action_pressed()));
    connect(ui->btn_action_sqrt, SIGNAL(released()), this, SLOT(action_pressed()));

    // Initialize unique buttons
    connect(ui->btn_action_clear, SIGNAL(released()), this, SLOT(clear()));
    connect(ui->btn_action_equals, SIGNAL(released()), this, SLOT(calculate()));
}

WinCalc::~WinCalc()
{
    delete ui;
}

// Manage operand buttons
void WinCalc::operand_pressed()
{
    QString displayStr = ui->display->text();
    QString operand = ((QPushButton *)sender())->text();

    if (operand.compare(".", Qt::CaseInsensitive) == 0)
    {
        if (displayStr.compare("0", Qt::CaseInsensitive) == 0)
        {
            ui->display->setText("0.");
        }
        else if (displayStr.contains(".", Qt::CaseInsensitive)) {} // Do nothing
        else
        {
            ui->display->setText(displayStr.append(operand));
        }
    }
    else
    {
        if (displayStr == "0")
        {
            ui->display->setText(operand);
        }
        else
        {
            ui->display->setText(displayStr.append(operand));
        }
    }
}

void WinCalc::operator_pressed()
{
    QString op = ((QPushButton *)sender())->objectName();

    // Reset triggers and buffer
    buffOperand = 0;
    op_add = false;
    op_sub = false;
    op_mul = false;
    op_div = false;
    op_mod = false;

    // Set trigger based on input
    if      (op.compare("btn_operator_add", Qt::CaseInsensitive) == 0) { op_add = true; }
    else if (op.compare("btn_operator_sub", Qt::CaseInsensitive) == 0) { op_sub = true; }
    else if (op.compare("btn_operator_mul", Qt::CaseInsensitive) == 0) { op_mul = true; }
    else if (op.compare("btn_operator_div", Qt::CaseInsensitive) == 0) { op_div = true; }
    else if (op.compare("btn_operator_mod", Qt::CaseInsensitive) == 0) { op_mod = true; }

    // Only set once per calculation to allow for operator changes
    if (ui->display->text().compare("", Qt::CaseInsensitive) != 0)
    {
        calcValue = ui->display->text().toDouble();
        ui->display->setText("");
    }

    override = true;
    set_display_small();
}

void WinCalc::action_pressed()
{
    QString action = ((QPushButton *)sender())->objectName();

    if (action.compare("btn_action_clear_entry", Qt::CaseInsensitive) == 0)
    {
        buffOperand == 0 ? ui->display->setText("") : clear();
    }
    else if (action.compare("btn_action_backspace", Qt::CaseInsensitive) == 0)
    {
        QString currValue = ui->display->text();
        currValue.chop(1);
        currValue.isEmpty() ? ui->display->setText("0") : ui->display->setText(currValue);
    }
    else if (action.compare("btn_action_sqrd", Qt::CaseInsensitive) == 0)
    {

    }
    else if (action.compare("btn_action_sqrt", Qt::CaseInsensitive) == 0)
    {

    }
    else if (action.compare("btn_action_sign", Qt::CaseInsensitive) == 0)
    {

    }
    else if (action.compare("btn_action_inv", Qt::CaseInsensitive) == 0)
    {

    }
}

void WinCalc::clear()
{
    calcValue = 0;
    override = false;
    op_add     = false;
    op_sub     = false;
    op_mul     = false;
    op_div     = false;
    op_mod     = false;
    ui->display->setText(QString::number(calcValue));
    ui->display_small->setText("");
}

void WinCalc::calculate()
{
    if (buffOperand == 0)
    {
        buffOperand = ui->display->text().toDouble();
    }

    set_display_small();

    if      (op_add) { calcValue += buffOperand; }
    else if (op_sub) { calcValue -= buffOperand; }
    else if (op_mul) { calcValue *= buffOperand; }
    else if (op_div) { calcValue /= buffOperand; }
    else if (op_mod)
    {
        double intTest;
        if (modf(calcValue, &intTest) != 0 || modf(buffOperand, &intTest) != 0)
        {
            clear();
            return;
        }

        calcValue = (int)calcValue % (int)buffOperand;
    }

    ui->display->setText(QString::number(calcValue));
}

void WinCalc::set_display_small()
{
    if (buffOperand == 0)
    {
        if      (op_add) { ui->display_small->setText(QString::number(calcValue) + " + "); }
        else if (op_sub) { ui->display_small->setText(QString::number(calcValue) + " - "); }
        else if (op_mul) { ui->display_small->setText(QString::number(calcValue) + " × "); }
        else if (op_div) { ui->display_small->setText(QString::number(calcValue) + " ÷ "); }
        else if (op_mod) { ui->display_small->setText(QString::number(calcValue) + " % "); }
    }
    else
    {
        if      (op_add) { ui->display_small->setText(QString::number(calcValue) + " + " + QString::number(buffOperand) + " ="); }
        else if (op_sub) { ui->display_small->setText(QString::number(calcValue) + " - " + QString::number(buffOperand) + " ="); }
        else if (op_mul) { ui->display_small->setText(QString::number(calcValue) + " × " + QString::number(buffOperand) + " ="); }
        else if (op_div) { ui->display_small->setText(QString::number(calcValue) + " ÷ " + QString::number(buffOperand) + " ="); }
        else if (op_mod) { ui->display_small->setText(QString::number(calcValue) + " % " + QString::number(buffOperand) + " ="); }
    }
}
