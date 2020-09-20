<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Add.aspx.cs" Inherits="User_Profile_Add" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
        <div>
        <UserControlLibrary:ValidationAlert ID="alert" AlertType="Success" runat="server" />
        <p>* required.</p>
        <div class="control-group">
            <label class="control-label">Name *</label>
            <div class="controls">
                <asp:TextBox ID="tbName" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="tbName" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Surname *</label>
            <div class="controls">
                <asp:TextBox ID="tbSurname" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="tbSurname" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Mail *</label>
            <div class="controls">
                <asp:TextBox ID="tbMail" TextMode="Email" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator3" ControlToValidate="tbMail" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Username *</label>
            <div class="controls">
                <asp:TextBox ID="tbUsername" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator4" ControlToValidate="tbUsername" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <p>Write your new password, if you want to change.</p>
        <div class="control-group">
            <label class="control-label">New Password</label>
            <div class="controls">
                <asp:TextBox ID="tbNewPassword" TextMode="Password" runat="server"></asp:TextBox>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">New Password Again</label>
            <div class="controls">
                <asp:TextBox ID="tbNewPasswordAgain" TextMode="Password" runat="server"></asp:TextBox>
            </div>
        </div>
        <div class="control-group">
            <div class="controls">
                <asp:LinkButton ID="lbtSubmit" OnClick="lbtSubmit_Click" Text="Submit" CssClass="btn btn-success" ValidationGroup="Submit" runat="server"></asp:LinkButton>
            </div>
        </div>
    </div>
</asp:Content>

