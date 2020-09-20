using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Reflection;
using System.Web;
using System.Web.UI;

namespace CodeLibrary.Sitemap
{
    public class SmartSiteMapProvider : XmlSiteMapProvider
    {
        public override void Initialize(string name, NameValueCollection attributes)
        {
            base.Initialize(name, attributes);
            this.SiteMapResolve += new SiteMapResolveEventHandler(SmartSiteMapProvider_SiteMapResolve);
        }

        public override SiteMapNode FindSiteMapNodeFromKey(string key)
        {
            SiteMapNode rootNode = SiteMap.Provider.RootNode;
            SiteMapNodeCollection collection = SiteMap.Provider.RootNode.GetAllNodes();

            if (rootNode["key"] == key)
                return rootNode;

            foreach (SiteMapNode node in collection)
            {
                if (node["key"] == key)
                    return node;
            }

            return null;
        }

        private SiteMapNode SmartSiteMapProvider_SiteMapResolve(object sender, SiteMapResolveEventArgs e)
        {
            if (SiteMap.CurrentNode == null)
                return null;

            SiteMapNode currentNodeClone = SiteMap.CurrentNode.Clone(true);

            SiteMapNode tempNode = currentNodeClone;
            while (tempNode != null)
            {
                NameValueCollection col = GetQueryString(tempNode, e.Context);
                if (col != null && col.Count != 0)
                {
                    tempNode.Url += NameValueCollectionToString(col);
                }

                tempNode = tempNode.ParentNode;
            }

            return currentNodeClone;
        }

        public NameValueCollection GetQueryString(SiteMapNode node, HttpContext context)
        {
            // Eğer bu node için tanımlanmış (virgül ile ayrılmış) queryString'ler varsa
            // bu queryString'ler ve değerleri bu collection'da toplanacak.
            NameValueCollection values = new NameValueCollection();

            // Bu node için sitemap'de queryString tanımlanmamış.
            if (node["queryString"] == null)
                return values;

            // Virgül'le ayrılmış queryString'leri al.
            string[] qstrings = node["queryString"].Split(",".ToCharArray());
            object page = HttpContext.Current.CurrentHandler;

            foreach (string qstring in qstrings)
            {
                string qs = qstring.Trim();
                string[] pair = qs.Split("=".ToCharArray());

                if (pair.Length == 1) // "=" olmadan yapılan kullanımlarda değeri QueryString'den al.
                {
                    // Eğer böyle bir QueryString yoksa umursama.
                    if (context.Request.QueryString[qs] == null)
                        continue;

                    values.Add(qs, context.Request.QueryString[qs]);
                }
                else if (pair.Length == 2) // "=" olan kullanımlarda değeri fonksiyon çağrısıyla al.
                {
                    // GetType .aspx'in RunTime Type'ını verir.
                    // İlk BaseType aspx.cs'nin Type'ıdır.
                    // İkinci BaseType'a gitmemizin sebebi BaseType'da abstract gibi bir fonksiyon tanımlaması yapılmasının şart koşulması.
                    // Çünkü eğer bir SiteMapNode fonksiyon çağrısı isteyen bir QueryString parametresine sahipse bu node'un tüm alt node'larında
                    // bu tanımlamanın yapılmış olması gerekir.
                    Type type = page.GetType().BaseType.BaseType;

                    MethodInfo method = type.GetMethod(pair[1]);
                    if (method == null)
                        throw new Exception(type.Name + " sınıfı " + pair[1] + " adlı bir fonksiyona sahip değil!");

                    values.Add(pair[0], method.Invoke(page, new object[] { }).ToString());
                }
                else
                    throw new Exception();
            }

            return values;
        }

        public string NameValueCollectionToString(NameValueCollection col)
        {
            string[] parts = new string[col.Count];
            string[] keys = col.AllKeys;

            for (int i = 0; i < keys.Length; i++)
                parts[i] = keys[i] + "=" + col[keys[i]];

            string url = "?" + String.Join("&", parts);
            return url;
        }
    }
}