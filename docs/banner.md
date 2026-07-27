# Banner

`banner.svg` is the source; `banner.png` is what the README shows (GitHub
renders PNG most reliably, and it does not depend on the viewer having the
fonts installed).

Editing the SVG by hand is the point — the stat numbers near the bottom of
the left column are plain text, so updating them when the question bank
grows is a one-line change instead of redrawing an image.

## Regenerating the PNG

Any Chromium-based browser can rasterize it headlessly. From the repository
root, with an absolute path to the SVG:

```powershell
& "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" `
    --headless --disable-gpu --hide-scrollbars `
    --force-device-scale-factor=1 --window-size=2560,1280 `
    --screenshot="docs/banner.png" `
    "file:///C:/full/path/to/docs/banner.svg"
```

```bash
google-chrome --headless --disable-gpu --hide-scrollbars \
    --force-device-scale-factor=1 --window-size=2560,1280 \
    --screenshot=docs/banner.png "file://$PWD/docs/banner.svg"
```

Afterwards, **open the PNG and look at it**. A malformed SVG still produces
a PNG — of the browser's XML error page — so a file appearing at the right
path proves nothing on its own. (Note that XML comments cannot contain a
double hyphen, which is exactly how this was broken once.)

## Keeping the numbers honest

The question count appears in three places that must agree:

- `docs/banner.svg` (the `QUESTIONS` stat)
- `README.md` (image alt text, both language sections)
- `CHANGELOG.md`

The real number is whatever `QuestionManager` loads; the test
`QuestionManager_NoDuplicateQuestionIds` walks the whole bank, so counting
ids there is the way to confirm it.
