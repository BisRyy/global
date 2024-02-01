const express = require('express');
const { exec } = require('child_process');
const path = require('path');
const fs = require('fs/promises'); // Using fs.promises for async file operations
const cors = require('cors');

const app = express();
const port = process.env.PORT || 3000;

app.use(cors({ origin: '*' }));  // Enable CORS for all routes
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

app.post('/run', async (req, res) => {
    const userCode = req.body.code;

    // path to compiled C++ binary
    const globalPath = path.join(__dirname, 'global');

    try {
        // Create a temporary file to store user code
        const tempFilePath = path.join(__dirname, 'temp', 'user_code.global');
        await fs.writeFile(tempFilePath, userCode);

        const command = `${globalPath} ${tempFilePath}`;

        exec(command, (error, stdout, stderr) => {
            console.log('stdout:', stdout);
            console.log('stderr:', stderr);

            // if (error) {
            //     console.error('Execution error:', error);
            //     return res.status(500).json({ error: 'Execution failed' });
            // }

            const result = {
                stdout: stdout.trim(),
                stderr: stderr.trim(),
            };

            res.json({ result });
        });
    } catch (err) {
        console.error('Error writing user code to file:', err);
        res.status(500).json({ error: 'Failed to write user code to file' });
    }
});

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});
