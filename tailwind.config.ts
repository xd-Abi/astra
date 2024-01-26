import type {Config} from "tailwindcss";

const config: Config = {
  content: ["./src/**/*.{js,ts,jsx,tsx,mdx}"],
  theme: {
    extend: {
      backgroundColor: {
        'midnight-blue': '#15161a'
      },
      backgroundImage:{
        'parallax': 'url("./623174.jpg")'
      }
    }
  },
  plugins: [],
};
export default config;
