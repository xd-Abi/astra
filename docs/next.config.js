const withNextra = require("nextra")({
  theme: "nextra-theme-docs",
  themeConfig: "./theme.config.tsx",
});

module.exports = withNextra({
  redirects: async () => {
    return [
      {
        source: "/",
        destination: "/start-here",
        permanent: true,
      },
    ];
  },
});
