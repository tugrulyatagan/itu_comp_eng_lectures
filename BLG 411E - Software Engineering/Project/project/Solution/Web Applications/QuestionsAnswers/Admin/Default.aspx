<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="Admin_Default" %>

<asp:Content ID="Content1" ContentPlaceHolderID="cphHead" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="cphLeft" Runat="Server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="cphMain" Runat="Server">
    <div class="alert alert-info span4">
        <%= new SiteMapLink("QA.Admin.Badge").ToString() %>
    </div>
    
    <div class="alert alert-info span4">
        <%= new SiteMapLink("QA.Admin.Tag").ToString() %>
        <br />
    </div>
</asp:Content>

