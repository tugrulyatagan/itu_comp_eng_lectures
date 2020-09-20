<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Login.aspx.cs" Inherits="Login" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div class="span6">
        <UserControlLibrary:ValidationAlert ID="alert" AlertType="Error" runat="server" />
        <div class="control-group">
            <label class="control-label">Username *</label>
            <div class="controls">
                <asp:TextBox ID="tbUsername" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="tbUsername" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Password *</label>
            <div class="controls">
                <asp:TextBox ID="tbPassword" TextMode="Password" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="tbPassword" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <div class="controls">
                <asp:LinkButton ID="lbtSubmit" OnClick="lbtSubmit_Click" Text="Please log me in" CssClass="btn btn-success" ValidationGroup="Submit" runat="server"></asp:LinkButton>
            </div>
        </div>
    </div>
</asp:Content>

