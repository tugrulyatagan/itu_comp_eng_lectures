<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Add.aspx.cs" Inherits="Admin_Tag_Add" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div>
        <p>* required.</p>
        <div class="control-group">
            <label class="control-label">Name *</label>
            <div class="controls">
                <asp:TextBox ID="tbName" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="tbName" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <label class="control-label">Information Text *</label>
            <div class="controls">
                <asp:TextBox ID="tbInformationText" TextMode="MultiLine" runat="server"></asp:TextBox>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="tbInformationText" ValidationGroup="Submit" ErrorMessage="*" runat="server"></asp:RequiredFieldValidator>
            </div>
        </div>
        <div class="control-group">
            <div class="controls">
                <asp:LinkButton ID="lbtSubmit" OnClick="lbtSubmit_Click" Text="Submit" CssClass="btn btn-success" ValidationGroup="Submit" runat="server"></asp:LinkButton>
            </div>
        </div>
    </div>
</asp:Content>

