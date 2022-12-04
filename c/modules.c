#include <stdio.h>

int main(){
    add_cookies_popup("../index.html");
}


// Adds "Accept cookies" pop-up dialog to your html page if one doesn't exist already.
// file_path can be relative, e.g. "./index.html", or full path, e.g. "C:\Users\USER\Desktop\project\index.html"
void add_cookies_popup(char *file_path){
    FILE *html_file = fopen(file_path, "r");
    if(html_file == NULL){
        printf("File %s does not exist.", file_path);
        return;
    }
    fseek(html_file, 0L, SEEK_END);
    int len = ftell(html_file);
    fseek(html_file, 0L, SEEK_SET);
    char *str = (char*) malloc(sizeof(char)*len);
    fread(str, 1, len, html_file);
    if(strstr(str, "cookies-eu-banner") != NULL){
        printf("Accept cookies pop-up already exists.\n");
        free(str);
        return;
    }

    if(strstr(str, "<body") == NULL){
        printf("There is no body tag in html file.\n");
        free(str);
        return;
    }

    char *str2 =
        "\n"
        "\n"
        "\n"
        "<!-- AUTOGENERATED ----------------------------------------------------------------->\n"
		"<!-- AUTOGENERATED ----------------------------------------------------------------->\n"
		"<!-- AUTOGENERATED ----------------------------------------------------------------->\n"
		"<!-- Cookie banner start -->\n"
        "\n"
		"<div class=\"cookies-eu-banner hidden\">\n"
		"	By clicking \"OK\", you agree to the storing of \n"
		"	<a href=\"#\">cookies</a> on your device to\n"
		"	enhance site navigation, analyze site usage, and improve marketing.\n"
		"	<button>Accept</button>\n"
		"</div>\n"
		"<script>\n"
		"	(() => {\n"
		"		const getCookie = (name) => {\n"
		"			const value = \" \" + document.cookie;\n"
		"			console.log(\"value\", `==${value}==`);\n"
		"			const parts = value.split(\" \" + name + \"=\");\n"
		"			return parts.length < 2 ? undefined : parts.pop().split(\";\").shift();\n"
		"		};\n"
        "\n"
		"		const setCookie = function (name, value, expiryDays, domain, path, secure) {\n"
		"			const exdate = new Date();\n"
		"			exdate.setHours(\n"
		"			exdate.getHours() +\n"
		"				(typeof expiryDays !== \"number\" ? 365 : expiryDays) * 24\n"
		"			);\n"
		"			document.cookie =\n"
		"			name +\n"
		"			\"=\" +\n"
		"			value +\n"
		"			\";expires=\" +\n"
		"			exdate.toUTCString() +\n"
		"			\";path=\" +\n"
		"			(path || \"/\") +\n"
		"			(domain ? \";domain=\" + domain : \"\") +\n"
		"			(secure ? \";secure\" : \"\");\n"
		"		};\n"
        "\n"
		"		const $cookiesBanner = document.querySelector(\".cookies-eu-banner\");\n"
		"		const $cookiesBannerButton = $cookiesBanner.querySelector(\"button\");\n"
		"		const cookieName = \"cookiesBanner\";\n"
		"		const hasCookie = getCookie(cookieName);\n"
        "\n"
		"		if (!hasCookie) {\n"
		"			$cookiesBanner.classList.remove(\"hidden\");\n"
		"		}\n"
        "\n"
		"		$cookiesBannerButton.addEventListener(\"click\", () => {\n"
		"			setCookie(cookieName, \"closed\");\n"
		"			$cookiesBanner.remove();\n"
		"		});\n"
		"	})();\n"
		"</script>\n"
		"<style>\n"
		"	.cookies-eu-banner {\n"
		"	background: #444;\n"
		"	color: #fff;\n"
		"	padding: 6px;\n"
		"	font-size: 13px;\n"
		"	text-align: center;\n"
		"	position: fixed;\n"
		"	bottom: 0;\n"
		"	width: 100%;\n"
		"	z-index: 10;\n"
		"	}\n"
        "\n"
		"	.cookies-eu-banner button {\n"
		"	text-decoration: none;\n"
		"	background: #222;\n"
		"	color: #fff;\n"
		"	border: 1px solid #000;\n"
		"	cursor: pointer;\n"
		"	padding: 4px 7px;\n"
		"	margin: 2px 0;\n"
		"	font-size: 13px;\n"
		"	font-weight: 700;\n"
		"	transition: background 0.07s, color 0.07s, border-color 0.07s;\n"
		"	}\n"
        "\n"
		"	.cookies-eu-banner button:hover {\n"
		"	background: #fff;\n"
		"	color: #222;\n"
		"	}\n"
        "\n"
		"	.hidden {\n"
		"	display: none;\n"
		"	}\n"
		"</style>\n"
        "\n"
		"<!-- Cookie banner end -->\n"
		"<!-- AUTOGENERATED ----------------------------------------------------------------->\n"
		"<!-- AUTOGENERATED ----------------------------------------------------------------->\n"
		"<!-- AUTOGENERATED ----------------------------------------------------------------->\n"
		"\n"
		"\n"
		"\n";

    char *str3 = strstr(str, "<body") + 5;
    for(int i = 0; i < 1000; i++){
        if(*(str3++) == '>') break;
    }
    fclose(html_file);
    html_file = fopen(file_path, "w");
    fwrite(str, 1, str3 - str, html_file);
    fwrite(str2, 1, strlen(str2), html_file);
    fwrite(str3, 1, strlen(str3), html_file);
    printf("Accept cookies pop-up added to your html file.");
}
