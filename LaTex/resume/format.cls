% [a4paper]
\usepackage[centering,paperwidth=210mm,paperheight=297mm,body={180mm,247mm}]{geometry}

\usepackage{
  array,
  booktabs,
  hyperref,
  color,
  latexsym,
  verbatim,
  url,
  ulem,
  xeCJK, % replace with CJK for sharelatex.com
  multirow,
  enumitem,
  fancyhdr,
  xcolor,
  tikz,
  calc % fix hbox too wide for heading, enable caculate
}

% \usepackage{latexsym,verbatim,url,CJKutf8}
\pagestyle{empty}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}
\urlstyle{same}

\hypersetup{
    colorlinks,%
    citecolor=black,%
    filecolor=black,%
    linkcolor=black,%
    urlcolor=black     % can put red here to better visualize the links
}

\definecolor{mygrey}{RGB}{29,32,136}
\definecolor{mygreylink}{RGB}{29,32,136}
\definecolor{labelgrey}{RGB}{29,32,136}



\raggedbottom
\raggedright
\setlength{\tabcolsep}{0in}
%\linespread{1.25}

%-----------------------------------------------------------
%Custom commands
\newcommand{\resitem}[1]{\item #1 \vspace{-2pt}}
\newcommand{\resheading}[1]{{\large \colorbox{mygrey}{\begin{minipage}{\textwidth-2\fboxsep}{\textbf{#1 \vphantom{p\^{E}}}}\end{minipage}}}}
\newcommand{\reslheading}[1]{{\large \colorbox{mygrey}{\begin{minipage}{0.8\textwidth-2\fboxsep}{\textbf{#1 \vphantom{p\^{E}}}}\end{minipage}}}}
\newcommand{\ressubheading}[4]{
\begin{tabular*}{\textwidth-5mm}{l@{\extracolsep{\fill}}r}
    \textbf{#1} \textit{#3} & #4 \quad #2 \\
\end{tabular*}\vspace{-6pt}}

% \newcommand{\ressubsingleheading}[3]{
% \begin{tabular*}{\textwidth-5mm}{@{\extracolsep{\fill}}lr}
%     \multirow{2}{*}{\textbf{#1}} & #2 \\
%     & #3 \\
% \end{tabular*}\vspace{-6pt}}

\newcommand{\ressubsingleline}[3]{
\begin{tabular*}{\textwidth-5mm}{ll@{\extracolsep{\fill}}r}
    \textbf{#1} & \quad\textit{#2} & #3 \\
\end{tabular*}}
