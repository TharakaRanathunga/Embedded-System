const fs = require('fs');
const { marked } = require('marked');

const markdown = fs.readFileSync('README.md', 'utf8');
const html = marked.parse(markdown, {
    headerIds: true
});

const fullHtml = `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 IoT Weather Station - README</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 900px;
            margin: 40px auto;
            padding: 20px;
            line-height: 1.6;
            color: #333;
        }

        h1, h2, h3 {
            color: #222;
        }

        code {
            background: #f4f4f4;
            padding: 2px 5px;
            border-radius: 4px;
        }

        pre {
            background: #f4f4f4;
            padding: 15px;
            overflow-x: auto;
            border-radius: 8px;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }

        th, td {
            border: 1px solid #ddd;
            padding: 10px;
            text-align: left;
        }

        th {
            background: #f2f2f2;
        }

        blockquote {
            border-left: 4px solid #999;
            padding-left: 15px;
            color: #666;
        }
    </style>
</head>
<body>
${html}
</body>
</html>
`;

fs.writeFileSync('README.html', fullHtml);

console.log('README.md converted to README.html');