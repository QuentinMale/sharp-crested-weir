# Marp Slides + GitHub Pages

This repository is configured to create slides from Markdown with Marp and publish them online through GitHub Pages.

## Write slides

Edit:

- `slides/index.md`

## Run locally

```bash
npm install
npm run watch
```

Marp will start a local preview server.

## Build locally

```bash
npm run build
```

Generated HTML will be:

- `dist/index.html`

## Publish online (GitHub Pages)

1. Push this repository to GitHub.
2. In GitHub: **Settings > Pages > Build and deployment**.
3. Set **Source** to **GitHub Actions**.
4. Push changes to `main`.

The workflow in `.github/workflows/deploy-slides.yml` will build and deploy the slides automatically.
